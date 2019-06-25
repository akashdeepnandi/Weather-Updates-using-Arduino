import mysql.connector
import serial
import time
import datetime

#database connector
mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  passwd="",
  database="w_db"
)
#database connector
def insert(data):
  checkFull()
  mycursor = mydb.cursor()

  sql = "INSERT INTO w_data(w_humid, w_temp, w_light, w_status, w_ap, w_ah, w_rp, w_rh, w_speed, w_mspeed, w_ts) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)"
  mycursor.execute(sql, data)

  mydb.commit()

def checkFull():
  mycursor = mydb.cursor()
  mycursor.execute("SELECT * FROM w_data")
  myresult = mycursor.fetchall()
  if len(myresult) >= 1000:
    full()

def full():
  mycursor = mydb.cursor()
  mycursor.execute("DELETE FROM w_data")


ser = serial.Serial("/dev/ttyACM0")#connection to arduino
while True:  # gonna use time.sleep(seconds)
    ser.write(b'x')
    x = str(ser.readline())
    val = x.split(',')
    x = list(val[9])
    val[9] = "".join(x[:-5])
    x = list(val[0])
    val[0] = "".join(x[2:])
    ts = datetime.datetime.fromtimestamp(time.time()).strftime('%Y-%m-%d %H:%M:%S')
    tup = (val[0],val[1],val[2],val[3],val[4],val[5],val[6],val[7],val[8],val[9],ts)
    print(tup)
    insert(tup)
    time.sleep(2)

