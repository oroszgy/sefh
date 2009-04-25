
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">

<head>
<META http-equiv="Content-Type" content="text/html; charset=UTF-8">
<%@page
contentType="text/html; charset=utf-8"
pageEncoding="utf-8" 
%>
<title>Indri search</title>
<link rel="stylesheet" type="text/css" href="style/style.css" title="stylesheet" />
</head>
<body>

<%@ page import="javax.naming.InitialContext" %>
<% InitialContext context = new InitialContext(); %>

<div id="content">
  <div id="header">
    <a href="http://www.lemurproject.org/indri"><h1>INDRI</h1></a>
    <h2>Language modeling meets inference networks</h2>
  </div>

  <form action="query.jsp" method="post">
    <div id="query">
     <textarea name="query" cols="90" rows="4"></textarea><br/>
     Use stemmed collection: <input type="checkbox" name="isStemmed" value="true"><br/>
     <input type="submit" value="Search"><br/>
     <br/>
     <%= (String) context.lookup( "java:comp/env/collection" ) %>
    </div> <!-- query -->
   </form>

</div> <!-- content -->

</body>
</html>

