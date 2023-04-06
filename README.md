![Wildetect](  https://github.com/JeanProfite/WildDetect/blob/main/images/logo_wildetect.png?raw=true )
# WildDetect
WildDetect est un projet étudiant visant à détecter les oiseaux et animaux aux alentours des aéroports afin de prévenir les risques aviaires.

Ce projet s'appuie sur deux composants principaux:
- Reconnaissance visuelle : [YoloV7](https://github.com/WongKinYiu/yolov7) avec le framework [NCNN](https://github.com/Tencent/ncnn) 
- Reconnaissance audio : [Birdnet-PI](https://github.com/mcguirepr89/BirdNET-Pi)
<p align="center">
  <img src="https://github.com/JeanProfite/WildDetect/blob/main/images/schema_bloc_globale.png?raw=true" width="800" />
</p>

<p align="center">
  <img src="https://github.com/JeanProfite/WildDetect/blob/main/images/schema_bloc.png?raw=true" width="700" hspace="20"/>
</p>


<p align="center">
  <img src="https://github.com/JeanProfite/WildDetect/blob/main/images/systeme_complet.png?raw=true" width="400" hspace="20"/>
  <img src="https://github.com/JeanProfite/WildDetect/blob/main/images/systeme_vue_globale.png?raw=true" width="400"/>
</p>

# CAO
<p align="center">
  <img src="https://github.com/JeanProfite/WildDetect/blob/main/images/support_camera.png?raw=true" width="500" hspace="20"/>
</p>

<p align="center">
  <img src="https://github.com/JeanProfite/WildDetect/blob/main/images/support2_raspberry_pi_4.png?raw=true" width="500" />
  <img src="https://github.com/JeanProfite/WildDetect/blob/main/images/support_raspberry_pi_4.png?raw=true" width="500" />
</p>

# Installation
Voir le [guide d'utilisation](https://elecron.notion.site/Guide-d-utilisation-WildDetect-ac3ef9db360b45738a5ac7c717ea15bc)
# Entrainement
Voir le repository [yolov7](https://github.com/WongKinYiu/yolov7) Pytorch
# Conversion du modèle
[export.py](https://github.com/WongKinYiu/yolov7/blob/main/export.py) --> Torchscript

[pnnx](https://github.com/pnnx/pnnx) (PyTorch Neural Network eXchange) --> .bin .param



# Lancement de WildDetect

## Dépendances
Pour lancer l'application, vous devez avoir:
- Un raspberry Pi 4 avec Bullseye 64-bit. [Install 64-bit OS](https://qengineering.eu/install-raspberry-64-os.html)
- Le framework Tencent ncnn installed. [Install ncnn](https://qengineering.eu/install-ncnn-on-raspberry-pi-4.html)
- OpenCV 64 bit installed. [Install OpenCV 4.5](https://qengineering.eu/install-opencv-4.5-on-raspberry-64-os.html)


## Compiler et lancer
```
git clone https://github.com/JeanProfite/WildDetect
cd WildDetect
```
Créé un dossier Release dans un dossier bin et un dossier recording
```
mkdir recording
mkdir bin
cd bin
mkdir Release
cd ..
cd ..
```

Pour compiler le programme, utilisez le script compile.sh
```
./compile.sh
```

Vous pouvez activer/désactiver les options suivantes dans yolov7main.cpp:

-L'affichage de la sortie vidéo (nécessite d'avoir configuré un serveur X11)

-L'enregistrement de la vidéo

Lancer le programme de détection
```
./bin/Release/YoloV7
```

Il est conseillé d'utiliser [tmux](https://github.com/tmux/tmux/wiki) afin que le programme continu à tourné lorsque le client ferme la connexion ssh.

A noté, le script toogle_birdnet_services.sh permet de désactiver/activer birdNET-PI.

# YoloV7 with the ncnn framework.
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
Paper: https://arxiv.org/pdf/2207.02696.pdf
Special made for a bare Raspberry Pi 4, see [Q-engineering deep learning examples](https://qengineering.eu/deep-learning-examples-on-raspberry-32-64-os.html)

