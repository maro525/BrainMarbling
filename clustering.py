import numpy as np
from sklearn.cluster import KMeans
import pandas as pd
import socket
import time
from contextlib import closing

df1 = np.loadtxt("../data_haga/haga_line.csv", delimiter=',', skiprows=1)
df2 = np.loadtxt("../data_haga/haga_book.csv", delimiter=',', skiprows=1)
df3 = np.loadtxt("../data_haga/haga_meditation.csv", delimiter=',', skiprows=1)
df4 = np.loadtxt("../data_haga/haga_music.csv", delimiter=',', skiprows=1)
df5 = np.loadtxt("../data_haga/haga_uttering.csv", delimiter=',', skiprows=1)

df = np.r_[df1, df2, df3, df4, df5]
print(df.shape)

km = KMeans(n_clusters=2, n_init=2)
pred = km.fit_predict(df)
ave = sum(pred)/len(pred)
print(ave)
sr = pd.Series(pred)
sr.to_csv("pred.csv")

# udp
host = '127.0.0.1'
port = 1111
send_port = 2222
bufsize = 4096

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

with closing(sock):
    sock.bind((host, port))
    while True:
        data_recv = sock.recv(bufsize)
        data_recv = data_recv.decode('utf-8')
        recv = data_recv.split("|")
        recv = recv[:5]
        recv = list(map(float,recv))
        print(recv)

        answer = km.predict(recv)[0]
        print(answer)
        msg = str(answer) + "|"
        msg = msg.encode('utf-8')
        sock.sendto(msg, (host, send_port))
        time.sleep(0.5)
