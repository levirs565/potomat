from krita import *

doc = Krita.instance().activeDocument()
baseName = fileName = doc.fileName()[:-4] 
fileList = []

for size in [16, 32, 64, 128]:
    newDoc = doc.clone()

    fileName = baseName + "_" + str(size) + ".png"
    info = InfoObject()
    info.setProperty("alpha", True)
    info.setProperty("compression", 9)
    info.setProperty("forceSRGB", True)

    xRes = newDoc.xRes()
    yRes = newDoc.yRes()

    newDoc.scaleImage(size, size, xRes, yRes , "Hermite")
    newDoc.exportImage(fileName, info)
    newDoc.close()
    
    fileList.append(fileName)
    
from subprocess import *
import os

icoFile = os.path.dirname(baseName) + "/icon.ico"
print(icoFile)
run(["png2ico", icoFile] + fileList)