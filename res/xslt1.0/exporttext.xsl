<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    
    <xsl:output method="text" version="1.0"
        encoding="UTF-8" indent="no"
        omit-xml-declaration="yes"/>
    
    <xsl:template match="/">
        <xsl:for-each select="/doc/body/row" >
            <xsl:for-each select="field" >
                <xsl:value-of select="text()" />
                <xsl:choose>
                    <xsl:when test="position() != last()">
                        <xsl:text>&#x9;</xsl:text>
                    </xsl:when>
                </xsl:choose>
            </xsl:for-each>
            <xsl:text>&#xa;</xsl:text>
        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>
