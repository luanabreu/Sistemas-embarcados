#!/usr/bin/env python
import sqlite3
import os
import sys
import cgi
import cgitb
from mq import *
import sys, time

# global variables
dbname='/var/www/gas.db'

# print the HTTP header
def printHTTPheader():
    print "Content-type: text/html\n\n"

# print the HTML head section
# arguments are the page title and the table for the chart
def printHTMLHead(title, table):
    print "<head>"
    print "    <title>"
    print title
    print "    </title>"

    print_graph_script(table)

    print "</head>"


# get data from the database
# if an interval is passed,
# return a list of records from the database
def get_data(interval):

    conn=sqlite3.connect(dbname)
    curs=conn.cursor()

    if interval == None:
        curs.execute("SELECT * FROM gas")
    else:
        curs.execute("SELECT * FROM gas WHERE timestamp>datetime('now','-%s hours') AND timestamp<=datetime('now')" % interval)

    rows=curs.fetchall()

    conn.close()
    return rows


# convert rows from database into a javascript table
def create_table(rows):
    chart_table=""

    for row in rows[:-1]:
        rowstr="[‘{0}’, {1}, {2}],\n”.format(str(row[0]),str(row[1]),str(row[2]))
        chart_table+=rowstr

    row=rows[-1]
    rowstr="[‘{0}’, {1}, {2}]\n”.format(str(row[0]),str(row[1]),str(row[2]))
    chart_table+=rowstr

    return chart_table


# print the javascript to generate the chart
# pass the table generated from the database info
def print_graph_script(table):

    # google chart snippet
    chart_code="""
    <script type="text/javascript" src="https://www.google.com/jsapi"></script>
    <script type="text/javascript">
      google.load("visualization", "1", {packages:[“corechart”]});
      google.setOnLoadCallback(drawChart);
      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          [‘Time’, ‘CO2’, ‘Gas LPG’],
%s
        ]);
        var options = {
          title: 'LPG e CO2'
        };
        var chart = new google.visualization.LineChart(document.getElementById('chart_div'));
        chart.draw(data, options);
      }
    </script>"""

    print chart_code % (table)

 


# print the div that contains the graph
def show_graph():
    print "<h2>CO Chart</h2>"
    print '<div id="chart_div" style="width: 900px; height: 500px;"></div>'

# connect to the db and show some stats
# argument option is the number of hours
def show_stats(option):

    conn=sqlite3.connect(dbname)
    curs=conn.cursor()

    if option is None:
        option = str(24)

    curs.execute("SELECT timestamp,max(temp) FROM gas WHERE timestamp>datetime('now','-%s hour') AND timestamp<=datetime('now')" % option)
    comax=curs.fetchone()
    comax="{0}&nbsp&nbsp&nbsp{1} %".format(str(tempmax[0]),str(tempmax[1]))

    curs.execute("SELECT timestamp,min(temp) FROM gas WHERE timestamp>datetime('now','-%s hour') AND timestamp<=datetime('now')" % option)
    comin=curs.fetchone()
    comin="{0}&nbsp&nbsp&nbsp{1} %".format(str(tempmin[0]),str(tempmin[1]))

    curs.execute("SELECT avg(temp) FROM gas WHERE timestamp>datetime('now','-%s hour') AND timestamp<=datetime('now')" % option)
    coavg=curs.fetchone()

    curs.execute("SELECT timestamp,max(humm) FROM gas WHERE timestamp>datetime('now','-%s hour') AND timestamp<=datetime('now')" % option)
    gas_lpgmax=curs.fetchone()
    gas_lpgmax="{0}&nbsp&nbsp&nbsp{1} C".format(str(hummmax[0]),str(hummmax[1]))

    curs.execute("SELECT timestamp,min(humm) FROM gas WHERE timestamp>datetime('now','-%s hour') AND timestamp<=datetime('now')" % option)
    gas_lpgmin=curs.fetchone()
    gas_lpgmin="{0}&nbsp&nbsp&nbsp{1} C".format(str(hummmin[0]),str(hummmin[1]))

    curs.execute("SELECT avg(humm) FROM  WHERE timestamp>datetime('now','-%s hour') AND timestamp<=datetime('now')" % option)
    gas_lpgavg=curs.fetchone()


    print "<hr>"


    print "<h2>Minumum Value&nbsp</h2>"
    print comin
    print gas_lpgmin
    print "<h2>Maximum Value</h2>"
    print comax
    print gas_lpgmax
    print "<h2>Average Value</h2>"
    print "%.1f" % coavg+"%"
    print "%.1f" % gas_lpgavg+"C"
    print "<hr>"

    print "<h2>In the last hour:</h2>"
    print "<table>"
    print "<tr><td><strong>Date/Time</strong></td><td><strong>CO</strong><td><strong>GAS_LPG</strong></td></td></tr>"

    rows=curs.execute("SELECT * FROM gas WHERE timestamp>datetime('now','-1 hour') AND timestamp<=datetime('now')")
    for row in rows:
        costr="<tr><td>{0}&emsp;&emsp;</td><td>{1} %</td><td>{2} C</td></tr>".format(str(row[0]),str(row[1]),str(row[2]))
        print costr
    print "</table>"

    print "<hr>"

    conn.close()

def print_time_selector(option):

    print """<form action="/cgi-bin/webgui.py" method="POST">
        Comportamento do CO2 e do gas LPG
        <select name="timeinterval">"""


    if option is not None:

        if option == "6":
            print "<option value=\"6\" selected=\"selected\">the last 6 hours</option>"
        else:
            print "<option value=\"6\">the last 6 hours</option>"

        if option == "12":
            print "<option value=\"12\" selected=\"selected\">the last 12 hours</option>"
        else:
            print "<option value=\"12\">the last 12 hours</option>"

        if option == "24":
            print "<option value=\"24\" selected=\"selected\">the last 24 hours</option>"
        else:
            print "<option value=\"24\">the last 24 hours</option>"

        if option == "168":
            print "<option value=\"168\" selected=\"selected\">the last 168 hours</option>"
        else:
            print "<option value=\"168\">the last 168 hours</option>"

    else:
        print """<option value="6">the last 6 hours</option>
            <option value="12">the last 12 hours</option>
            <option value="24">the last 24 hours</option>
            <option value="168">the last 168 hours</option>"""

    print """        </select>
        <input type="submit" value="Display">
    </form>"""


# check that the option is valid
# and not an SQL injection
def validate_input(option_str):
    # check that the option string represents a number
    if option_str.isalnum():
        # check that the option is within a specific range
        if int(option_str) > 0 and int(option_str) <= 24:
            return option_str
        else:
            return None
    else:
        return None


#return the option passed to the script
def get_option():
    form=cgi.FieldStorage()
    if "timeinterval" in form:
        option = form[“timeinterval”].value
        return validate_input (option)
    else:
        return None

# main function
# This is where the program starts
def main():

    cgitb.enable()

    # get options that may have been passed to this script
    option=get_option()

    if option is None:
        option = str(24)

    # get data from the database
    records=get_data(option)

    # print the HTTP header
    printHTTPheader()

    if len(records) != 0:
        # convert the data into a table
        table=create_table(records)
    else:
        print "No data found"
        return

    # start printing the page
    print "<html>"
    # print the head section including the table
    # used by the javascript for the chart
    printHTMLHead("Monitor de Gases Polentes", table)

    # print the page body
    print "<body>"
    print "<h1>Monitor de Gases Polentes</h1>"
    print "<hr>"
    print_time_selector(option)
    show_graph()
    show_stats(option)
    print "</body>"
    print "</html>"

    sys.stdout.flush()

if __name__=="__main__":
    main()
