<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<META http-equiv="Content-Type" content="text/html; charset=UTF-8">
<%@page contentType="text/html; charset=utf-8" pageEncoding="utf-8"%>
<%@page
	import="javax.naming.InitialContext,edu.umass.cs.indri.web.*,java.util.regex.*,edu.umass.cs.indri.*,edu.umass.cs.indri.hits.*,java.util.*,java.lang.*,lemurproject.indri.*,javax.naming.InitialContext"%>

<title>SEFH</title>
<link rel="stylesheet" type="text/css" href="style/style.css"
	title="stylesheet" />
</head>
<body>

<div id="content">
<div id="header">
<h1><a href="http://code.google.com/p/sefh">SEFH</a></h1>
<h2>Országgyűlési naplók</h2>
</div>

<!-- content -->
<%
	String query = "";
	Boolean isStemmed = true;
	Boolean isStopped = true;
	InitialContext context = new InitialContext();
	//TEST
	//String w = "parlament;költségvetés;kereskedelem;törvény;előterjesztés";
	//w +="külügyi bizottság;kormánypárti frakciók;módosító indítvány;Orbán Viktor;Gyurcsány Ferenc";
	//w +="Antall Imre emlék;Parlament létszám csökkentés;módosító javaslat elfogadás;ellenzék Fidesz szavazás;köztársasági elnök választás";
	//w +="kormány autópálya építés korrpució;választási költségvetés költekezés hazugság;ülés felszólal Horn Gyula;Torgyán József mondjon le";
	//out.println(test(Arrays.asList(w.split(";")), context));
	//ENDTEST
	if (request != null && request.getParameter("query") != null) {
		query = new String(request.getParameter("query")
				.getBytes("ISO-8859-1"), "UTF-8");
		if (query != "") {
			String isStemmedString = request.getParameter("isStemmed");
			String isStoppeddString = request.getParameter("isStopped");
			isStemmed = (isStemmedString == null ? false : true);
			isStopped = (isStoppeddString == null ? false : true);
		}
	}
%>

<form action="index.jsp" method="get">
<div id="query">
	<input type="text" name="query" size="70" value="<%=query%>">
	<inputtype="submit" value="Search"><br />
	Szótövezés 
	<input type="checkbox" name="isStemmed" <%if(isStemmed) out.print("checked");%>></input><br />
	Tiltilistás szavak szűrése
	<input type="checkbox" name="isStopped" <%if(isStopped) out.print("checked");%>></input><br />
<br />
</div>
<!-- query --></form>
</div>

<%
	out.println(getQueryResult(query, isStemmed, isStopped, context));
%>
</body>
</html>

<%!Integer documentID = null;%>

<%!public String getQueryResult(String queryString,
			boolean useStemmedCollection, boolean useStoppedCollection, InitialContext context) {

	
		long beginQuery = System.currentTimeMillis();
		long endQuery = 0;
		long endRerankTime = 0;
		long endDocumentTime = 0;

		try {
			String stemmedIndexName = (String) context
					.lookup("java:comp/env/index.indri.stemmed");
			String stoppedIndexName = (String) context
					.lookup("java:comp/env/index.indri.stopped");
			String stemmedStoppedIndexName = (String) context
			.lookup("java:comp/env/index.indri.stemmedstopped");
			String plainIndexName = (String) context
			.lookup("java:comp/env/index.indri.plain");
			
			boolean rerank = ((Boolean) context.lookup("java:comp/env/rerank"))
					.booleanValue();
			int rerankCount = ((Integer) context
					.lookup("java:comp/env/rerankCount")).intValue();
			int resultCount = ((Integer) context
					.lookup("java:comp/env/resultCount")).intValue();
			String database = (String) context.lookup("java:comp/env/index.db");
			String dbuser = (String) context
					.lookup("java:comp/env/index.dbuser");
			String dbpassword = (String) context
					.lookup("java:comp/env/index.dbpassword");
			boolean judge = ((Boolean) context.lookup("java:comp/env/judge"))
					.booleanValue();

			//creating query environment
			QueryEnvironment qenv = new QueryEnvironment();
			String indexName;
			if (useStemmedCollection && useStoppedCollection)
				indexName = stemmedStoppedIndexName;
			else if(useStemmedCollection)
				indexName = stemmedIndexName;
			else if(useStoppedCollection)
				indexName = stoppedIndexName;
			else
				indexName = plainIndexName;
			qenv.addIndex(indexName);

			int[] reranked = null;
			ScoredExtentResult[] results = null;
			QueryAnnotation annotation = null;

			if (rerank) {
				results = qenv.runQuery(queryString, rerankCount);
				endQuery = System.currentTimeMillis();

				Query hits = new Query();
				reranked = hits.rerank(qenv, database, "mysql", dbuser,
						dbpassword, results, resultCount);
				annotation = qenv.runAnnotatedQuery(queryString, reranked,
						reranked.length);
				endRerankTime = System.currentTimeMillis();
			} else {
				annotation = qenv.runAnnotatedQuery(queryString, resultCount);

				reranked = new int[annotation.getResults().length];
				for (int i = 0; i < reranked.length; i++) {
					reranked[i] = annotation.getResults()[i].document;
				}

				endQuery = endRerankTime = System.currentTimeMillis();
			}

			ParsedDocument documents[] = qenv.documents(reranked);
			endDocumentTime = System.currentTimeMillis();

			double queryTime = (endQuery - beginQuery) / 1000.0;
			double rerankTime = (endRerankTime - endQuery) / 1000.0;
			double documentTime = (endDocumentTime - endRerankTime) / 1000.0;
			String resultHeader = "<div id=\"content\">\n"
					+ "<div id=\"resultbanner\">\n" + "<h2>Results for "
					+ queryString + "</h2>\n" + "Query: " + queryTime
					+ "s | Documents: " + documentTime + "s | Rerank: "
					+ rerankTime + "s\n" + "</div> <div id=\"results\">\n";

			String queryResult = "";
			for (int i = 0; i < documents.length; i++) {
				ParsedDocument doc = documents[i];
				Map meta = doc.metadata;
				String text = doc.text;
				ParsedDocument.TermExtent[] positions = doc.positions;

				byte[] docnoBytes = (byte[]) meta.get("docno");
				byte[] titleBytes = (byte[]) meta.get("title");
				byte[] urlBytes = (byte[]) meta.get("url");
				String title = null;
				String url = null;
				String docno = null;

				if (titleBytes != null)
					title = Query.getStringFromCBytes(titleBytes);
				if (urlBytes != null)
					url = Query.getStringFromCBytes(urlBytes);
				if (docnoBytes != null)
					docno = Query.getStringFromCBytes(docnoBytes);

				if (title == null)
					title = docno;

				String beginLink = url != null ? ("<a href=\"" + url + "\">")
						: "";
				String endLink = url != null ? "</a>" : "";
				String snippet = SnippetBuilder.buildSnippet(annotation,
						reranked[i], text, positions, 100, 10, 35);
				documentID = new Integer(reranked[i]);

				queryResult += "<div id=\"result\">\n" + "<h2>" + String.valueOf(i+1) + beginLink
						+ title + endLink + "</h2>\n" + "<div id=\"snippet\">"
						+ snippet + "</div>\n"
						+ "[ <a href=\"showdoc.jsp?documentID=" + documentID
						+ "&index=" + indexName + "\">Cached</a> ]</div>\n";
				//+ "</div>\n";
			}
			qenv.close();
			return resultHeader + "\n" + queryResult;
		} catch (Throwable e) {
			System.out.println(e.getMessage());
			System.out.println("An exception occured");
		}
		return "";
	}%>
