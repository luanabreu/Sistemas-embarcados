#!/usr/bin/env python

import sqlite3
import Adafruit_DHT
import os
import time
import glob
from mq import *
import sys, time

# global variables
dbname='/var/www/gas.db'

# store the temperature and hummidity in the database
def log_gas(CO,GAS_LPG):

    conn=sqlite3.connect(dbname)
    curs=conn.cursor()

    curs.execute("INSERT INTO gas values(datetime('now'), (?), (?))", (CO,GAS_LPG))
    #curs.execute("INSERT INTO temp_hum values(datetime('now'), (?))", (GAS_LPG,))
    # commit the changes
    conn.commit()

    conn.close()


# display the contents of the database
def display_data():

    conn=sqlite3.connect(dbname)
    curs=conn.cursor()

    for row in curs.execute("SELECT * FROM gas"):
        print str(row[0])+”     “+str(row[1])+”        “+str(row[2])

    conn.close()

# get temerature and humidity
# returns None on error, or the temperature,humidity as a float
def get_gas():
        try:
                mq = MQ();
                perc = mq.MQPercentage()
                GAS_LPG = perc["GAS_LPG"]
                CO = perc["CO"]
                return CO, GAS_LPG
            
        except:
                return None, None

# main function
def main():
        # get the gas from the device file
        CO, GAS_LPG = get_gas()
        # Store data to DB in case we have values
        if (CO != None and GAS_LPG !='None'):
                log_gas(CO, GAS_LPG)
#       display_data()

if __name__=="__main__":
    main()
