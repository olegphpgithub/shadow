<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
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
                <script type="text/javascript">
<![CDATA[
function search(pWorksheetId) {
    var lSearch = document.getElementById("S"+pWorksheetId).value.toUpperCase(),
        lRows = document.getElementById("data"+pWorksheetId).getElementsByTagName("TR"),
        lRowCount = lRows.length;
    for (var i = 0; i < lRowCount; i++){
        if (lSearch==="") {
            lRows[i].style.display = "";
        } else {
            var lCells = lRows[i].getElementsByTagName("TD");
            lCellCount = lCells.length;
            lFound = false;
            for (var j=0; (!lFound && j<lCellCount);j++) {
                if (lCells[j].innerHTML.toUpperCase().indexOf(lSearch) != -1)
                    lFound = true;
            }
            lRows[i].style.display = (lFound ? "" : "none");
        }
    }
};

function searchIfEnter(e, pWorksheetId){
    var keycode;
    if(window.event) {
        keycode = window.event.keyCode;
    } else if (e) {
        keycode = e.which;
    } else {
        return true;
    }
    if(keycode == 13) {
        search(pWorksheetId);
    return false;
    } else {
        return true;
    }
};
]]>
                </script>
            </head>
            <body>
                <table border="0" cellpadding="0" cellspacing="0" class="html_export">
                    <tr>
                        <td>Search: <input type="text" size="30" maxlength="1000" value="" id="S2468" onkeydown="return searchIfEnter(event, '2468');" />
                        <input type="button" value="Search" onclick="search('2468')"/></td>
                    </tr>
                </table>
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
                    <tbody id="data2468">
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
