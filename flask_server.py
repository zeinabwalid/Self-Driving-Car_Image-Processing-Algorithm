#!flask/bin/python
import os
import cv2
from PIL import Image
from io import BytesIO
import base64
import requests
from flask import Flask, request
app = Flask(__name__)

@app.route('/upload',methods=['POST'])
def upload():
    req_data = request.get_json()
    file = req_data["file"]
    starter = file.find(',')
    image_data = file[starter+1:]
    image_data = bytes(image_data, encoding="ascii")
    im = Image.open(BytesIO(base64.b64decode(image_data)))
    folder = os.path.join('images/')
    if not os.path.isdir(folder):
        os.mkdir(folder)
        im.save('images/image.png')
    else:
        im.save('images/image.png')

    return "Done"    



if __name__ == "__main__":
    app.run(debug=True,port=3000,host="192.168.43.187")  
    