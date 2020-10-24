# multiphysix
## Personal Data
Name: Muhammad Adhipatiunus<br/>
NIM: 13617053</br>
## Personal Motivation
This repository is dedicated for advancement of science and technology and is free-for-all. The developer goal is to provide professional and other developers a robust, modular, and practical way to simulate the physical world. This repository is open for all interested in developing a computer simulation for any field of study. <br/>
I am interested to implement my computational scheme on Google's Cloud High Performance Computing platform. One of the product I am excited to try is **virtual GPU-accelerated Linux workstation** in Compute Engine API, I have explored the product and the summary will be given below.<br/>
## Product Research
To be able to access the workstation, user must first create a project directory and billing profile in Google Cloud for Compute Engine API. User must also setup Teradici Client which is the middleware between user's computer and Google's virtual workstation.<br/>
![schematic](https://cloud.google.com/solutions/images/creating-a-virtual-linux-workstation-architecture.svg "Schematic")
<br/>
User can then initiate Compute Engine virtual workstation by typing in Google Cloud console. <br/>
>gcloud compute instances create *name* \
>    --machine-type *machine-type* \
>    --accelerator type=*accelerator*,count=*num-gpus* \
>    --can-ip-forward \
>    --maintenance-policy "TERMINATE" \
>    --tags "https-server" \
>    --image-project centos-cloud \
>    --image-family centos-7 \
>    --boot-disk-size *size*

User is then required to setup NVIDIA driver, Teradici PCoIP client, and firewall setup for the virtual workstation. After setup user can then remotely access the virtual workstation from their device.
![ve](https://cloud.google.com/solutions/images/creating-a-virtual-linux-workstation-linux-desktop.jpg "ve")
## Sample Code
Since my billing account has yet to be verified by Google, I cannot access the API. But I have made a code for computing partial differential numerically using LSMPS method which is often used to solve incompressible Navier Stokes equation. The code is still in early development but it can serve as a reference to my familiarity with CPP STL and ADT. The code is on this repo titled LSMPS_V01.cpp, you can also kindly check my other repos (mostly aerial robotics and numerical simulation).
