
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">

<head>
<META http-equiv="Content-Type" content="text/html; charset=UTF-8">
<%@page contentType="text/html; charset=utf-8" pageEncoding="utf-8"%>
<title>Document result</title>
</head>
<body>

<%@ page
	import="javax.naming.InitialContext,edu.umass.cs.indri.*,edu.umass.cs.indri.hits.*,java.util.*,java.lang.*,lemurproject.indri.*"%>

<%
	InitialContext context = new InitialContext();
	boolean preformatted = ((Boolean) context
			.lookup("java:comp/env/preformatted")).booleanValue();
	int numericDocID = Integer.parseInt(request
			.getParameter("documentID"));
	String index = new String(request.getParameter("index")
			.getBytes("ISO-8859-1"), "UTF-8");
	// make a query environment.
	QueryEnvironment env = new QueryEnvironment();
	env.addIndex(index);
	int[] documentIDs = new int[1];
	documentIDs[0] = numericDocID;

	ParsedDocument[] docs = env.documents(documentIDs);
%>

<%
	if (preformatted) {
%>
<pre>
<%
	}
%>
<%=docs[0].text%>
<%
	if (preformatted) {
%>
     </pre>
<%
	}
%>
<%
	env.close();
%>

</body>
</html>

