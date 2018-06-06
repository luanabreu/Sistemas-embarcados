#!/usr/bin/env

import sqlite3
import Adafruit_DHT
import os
import time
import glob

# global variables
dbname='/var/www/templog.db'

# store the temperature and hummidity in the database
def log_temperature(temp,humm):

    conn=sqlite3.connect(dbname)
    curs=conn.cursor()

    curs.execute("INSERT INTO temp_hum values(datetime('now'), (?), (?))", (temp,humm))
    #curs.execute("INSERT INTO temp_hum values(datetime('now'), (?))", (humm,))
    # commit the changes
    conn.commit()

    conn.close()


# display the contents of the database
def display_data():

    conn=sqlite3.connect(dbname)
    curs=conn.cursor()

    for row in curs.execute("SELECT * FROM temp_hum"):
        print str(row[0])+”     “+str(row[1])+”        “+str(row[2])

    conn.close()

# get temerature and humidity
# returns None on error, or the temperature,humidity as a float
def get_temp_hum():
        try:
                humm, temp = Adafruit_DHT.read_retry(Adafruit_DHT.DHT22, 4)
                humm = round (humm, 2)
                temp = round (temp, 2)
                return humm, temp
        except:
                return None, None

# main function
# This is where the program starts
def main():
        # get the temperature from the device file
        humm, temp = get_temp_hum()
        # Store data to DB in case we have values
        if (humm != None and temp !='None'):
                log_temperature(humm, temp)
#       display_data()

if __name__=="__main__":
    main()
