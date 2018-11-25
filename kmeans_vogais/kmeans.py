#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov 24 17:45:00 2018

@author: victor
"""

import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np

#LENDO IMAGEM
img = cv.imread("/home/victor/Área de Trabalho/OpenCV_Codes/img/a.jpg", cv.IMREAD_GRAYSCALE)
img = cv.resize(img, (0,0), fx=.5, fy=.5, interpolation=cv.INTER_LINEAR)

#IMPRIMINDO IMAGEM
plt.figure(figsize=(9,18))
plt.subplot(3,1,1), plt.imshow(img, cmap='gray')
plt.title('Imagem original')#, plt.xticks([]), plt.yticks([])

plt.subplot(3,1,2), plt.hist(img.ravel(), 256)
plt.title('Histograma original')#, plt.xticks([]), plt.yticks([])

plt.subplot(3,1,3), plt.hist(img.ravel(), 256, log=True)
plt.title('Histograma logarítmico')#, plt.xticks([]), plt.yticks([])
plt.show()

#SEGMENTANDO
ret, segmentada = cv.threshold(img, 0, 255, cv.THRESH_BINARY+ cv.THRESH_OTSU)

plt.figure(figsize=(9, 18))
plt.imshow(segmentada, cmap='gray'), plt.title('Segmentada por Otsu'), plt.xticks([]), plt.yticks([])
plt.show()

'''
#ABERTURA
kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, (3,3))
aberta = cv.morphologyEx(segmentada, cv.MORPH_OPEN, kernel)

plt.figure(figsize=(9, 18))
plt.imshow(aberta, cmap='gray'), plt.title('Aberta com elipse 3x3'), plt.xticks([]), plt.yticks([])
plt.show()
'''
#HISTOGRAMA
hist = cv.calcHist([segmentada], [0], None, [256], [0, 256])
print('Quantidade de pixels pretos: {}; brancos: {}'.format(hist[0],hist[255]))
plt.stem(hist), plt.title('Histograma da aberta')
plt.show()

#CRIANDO DADOS
pontos = []
rows, cols = segmentada.shape
for i in range(rows):
    for j in range(cols):
        if segmentada[i,j] == 0:
          pontos.append(np.array([i,j], dtype = np.float32))  
pontos = np.array(pontos)

#CLUSTERIZAÇÃO POR KMEANS
K = 120
criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 10, 1.0)
flag = cv.KMEANS_PP_CENTERS
compactness, labels, centros = cv.kmeans(pontos, K, None, criteria, 10, flag)

'''
#SEPARANDO VOGAIS COM TAMANHO FIXO
ind=0; tam = 25
for x,y in centros:
    #print('({},{})'.format(int(x), int(y)))
    cv.imwrite('a{}.jpg'.format(ind), segmentada[int(x)-tam:int(x)+tam, int(y)-tam:int(y)+tam])
    ind+=1
'''


#SEPARANDO VOGAIS COM TAMANHO ADAPTÁVEL
ind=0
for lin, col in centros:
    tam=3  # tamanho do quadrado inicial
    x = int(lin)
    y = int(col)
    while True:
        t = tam//2
        #VERIFICA SE HÁ UM PIXEL PRETO NA BORDA DO QUADRADO
        borda1 = segmentada[x-t:x+t, y-t:y-t+1].flatten() # vertical esquerda; print('borda1: [{}, {}:{}]'.format(y-t, x-t, x+t)); 
        borda2 = segmentada[x-t:x+t, y+t:y+t+1].flatten() # vertical direita; print('borda2: [{}, {}:{}]'.format(y+t, x-t, x+t)); 
        borda3 = segmentada[x-t:x-t+1, y-t:y+t].flatten() # horizontal cima; print('borda3: [{}:{}, {}]'.format(y-t, y+t, x-t)); 
        borda4 = segmentada[x+t:x+t+1, y-t:y+t].flatten() # horizontal baixo; print('borda4: [{}:{}, {}]'.format(y-t, y+t, x+t)); 
        bordas = np.append(borda1, [borda2, borda3, borda4]) # mistura tudo
        if 0 in bordas:
            print('0 in bordas for t={}'.format(t))
            tam+=2
            break
        else: 
            tam+=2  # próximo ímpar
        
    while True:
        t = tam//2
        #VERIFICA SE TODOS OS PIXELS NA BORDA DO QUADRADO SÃO BRANCOS
        borda1 = segmentada[x-t:x+t, y-t:y-t+1].flatten() # vertical esquerda
        borda2 = segmentada[x-t:x+t, y+t:y+t+1].flatten() # vertical direita
        borda3 = segmentada[x-t:x-t+1, y-t:y+t].flatten() # horizontal cima
        borda4 = segmentada[x+t:x+t+1, y-t:y+t].flatten() # horizontal baixo
        bordas = np.append(borda1, [borda2, borda3, borda4]) # mistura tudo
        if 0 not in bordas:
            print('0 not in bordas for t= {}'.format(t))
            letra = cv.resize(segmentada[x-t:x+t, y-t:y+t], (25,25), cv.INTER_LINEAR)
            cv.imwrite('a{}.jpg'.format(ind), letra)
            break
        else:
            tam+=2
    ind+=1




'''DEPÓSITO DE CÓDIGOS

a = [1,2,3,4]
b = [11,22,33,44]
c = [5,6,7,8]

d = np.append(a, [b,c, a])
1 in d



a = np.array([[1,2,3],[4,5,6],[7,8,9]])
a[0:1, 0:3]

'''