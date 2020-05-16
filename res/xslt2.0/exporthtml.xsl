<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:fn="http://www.w3.org/2005/xpath-functions"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    
    <xsl:output indent="yes"/>
    
    <xsl:template match="/">
        
        <html>
            <head>
                <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
                <title><xsl:value-of select="/doc/head/name/text()"/></title>
                <style type="text/css">
table.html_export {
    background-color:#F2F2F5;
    border-width:1px 1px 0px 1px;
    border-color:#C9CBD3;
    border-style:solid;
}
table.html_export td {
    color:#000000;
    font-family:Arial,Helvetica,sans-serif;
    font-size:9pt;
    background-color:#EAEFF5;
    padding:8px;
    background-color:#F2F2F5;
    border-color:#ffffff #ffffff #cccccc #ffffff;
    border-style:solid solid solid solid;
    border-width:1px 0px 1px 0px;
}
table.html_export th {
    font-family:Arial,Helvetica,sans-serif;
    font-size:9pt;
    padding:8px;
    background-color:#CFE0F1;
    border-color:#ffffff #ffffff #cccccc #ffffff;
    border-style:solid solid solid none;
    border-width:1px 0px 1px 0px;
    white-space:nowrap;
}
                </style>
            </head>
            <body>
                <table border="0" cellpadding="0" cellspacing="0" class="html_export">
                    <thead>
                        <tr>
                            <xsl:for-each select="/doc/head/field">
                                <th>
                                    <xsl:attribute name="id">
                                        <xsl:value-of select="./@name" />
                                    </xsl:attribute>
                                    <xsl:value-of select="./text()" />
                                </th>
                            </xsl:for-each>
                        </tr>
                    </thead>
                    <tbody>
                        <xsl:for-each select="/doc/body/row">
                            <tr>
                                <xsl:for-each select="./field">
                                    <td>
                                        <xsl:attribute name="headers">
                                            <xsl:value-of select="./@name" />
                                        </xsl:attribute>
                                        <xsl:value-of select="./text()" />
                                    </td>
                                </xsl:for-each>
                            </tr>
                        </xsl:for-each>
                    </tbody>
                </table>
            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>
