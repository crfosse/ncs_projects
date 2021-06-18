# nRF91 to Google Cloud
This project covers how to connect to Google Cloud with an nRF9160 DK. The nRF91 is using MQTT protocol to communicate with Google Cloud IoT Core, a service that  connects to and manages IoT Devices.

We used the Cloud IoT Core to get data from the nRF91 into Pub/Sub, which is Google Cloud’s internal messaging service that allows us to send and receive messages from and to IoT devices. From here we used Cloud Functions as a functionality to react on, among other things, Pub/Sub events or HTTP triggers. 

## Disclaimer
This is a student project , and thus we can not guarantee that everything will work perfectly or be up to date.
## Required tools
- [nRF9160 DK](https://www.nordicsemi.com/Software-and-Tools/Development-Kits/nRF9160-DK)
- [nRF Connect for Desktop](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Connect-for-desktop)
- [Google Cloud SDK](https://cloud.google.com/sdk/docs/#install_the_latest_cloud_tools_version_cloudsdk_current_version)
- [Node.js](https://nodejs.org/en/) and npm (which you get when installing Node.js)
## nRF9160 DK setup
Open nRF Connect and add the app Getting Started Assistant. Then launch it and follow its instructions.
## nRF9160 DK configuration
In prj.conf you need to change the following configuration to match your project
```c
CONFIG_GCLOUD_PROJECT_NAME="PROJECT_NAME"
CONFIG_GCLOUD_REGISTRY_NAME="REGISTRY_NAME"
CONFIG_GCLOUD_DEVICE_NAME="DEVICE_NAME"
```
### Generating keys
To connect to Google Cloud, you will need to generate keys for your device. In src\private_info run the following command
```console
python create_keys.py -d DEVICE_NAME -e
```
## Google Cloud Platform
Install Google Cloud Tools and run Google Cloud SDK Shell

Authenticate Google Cloud
```console
gcloud auth login
```
Create a Google Cloud project
```console
gcloud projects create PROJECT_NAME
gcloud config set project PROJECT_NAME
```
Set up permissions
```console
gcloud projects add-iam-policy-binding PROJECT_NAME --member=serviceAccount:cloud-iot@system.gserviceaccount.com --role=roles/pubsub.publisher
```
Create a Pub/Sub topic
```console
gcloud pubsub topics create TOPIC_NAME
```
Optional: Make a subscription. This can be used to check for messages yourself
```console
gcloud pubsub subscriptions create --topic TOPIC_NAME SUBSCRIPTION_NAME
```
Create a registry
```console
gcloud iot registries create REGISTRY_NAME --region=us-central1 --event-notification-config=topic=projects/PROJECT_NAME/topics/TOPIC_NAME
```
Create a device. The public key path must point to the file containing your ES256 key, "DEVICE_NAME-cert.pem"
```console
gcloud iot devices create DEVICE_ID --project=PROJECT_NAME --region=us-central1 --registry=REGISTRY_NAME --public-key path=DEVICE_NAME-cert.pem,type=es256-x509-pem
```
After your device has successfully connected to Google Cloud you can check for messages in Pub/Sub
```console
gcloud pubsub subscriptions pull --auto-ack SUBSCRIPTION_NAME
``` 

## Cloud Functions
As in the Getting Started Assistant, Chocolatey will be used to install packages for cloud functions. Firebase will be used both as a database and to deploy the cloud functions. Nodejs version 8 is needed for the cloud functions. As of 7/12/2019 Google Cloud use 8.15.0, so lets use the same.
```console
choco install nodejs --version 8.15.0
```
Npm is the package manager for nodejs, and will be used to install firebase and its packages. Npm installs into current folder by default. However, it can be told to install a package globally if used with "-g".
```console
npm install -g firebase-tools
```
Follow this [firebase cloud functions toturial](https://www.youtube.com/watch?v=DYfP-UIKxH0&t=256s), but with javascript and install some extra packages in the functions folder. These are the same as included in the top of the index.js file.
```console
mkdir gcloud && cd gcloud
firebase login
firebase init
cd functions
npm install firebase-functions firebase-admin @google-cloud/pubsub @google-cloud/iot node-fetch cors
firebase deploy
```
PS: On windows you might need to specify the path of the firebase.cmd file found in: C:\Users\<user>\AppData\Roaming\npm

The cJSON library is based on [this](https://github.com/DaveGamble/cJSON) cJSON library by [Dave Gamble](https://github.com/DaveGamble)

## Resources
- [Google Cloud](https://cloud.google.com/)
- [Cloud Pub/Sub](https://cloud.google.com/pubsub/)
- [Nordic Semiconductor Playground](https://github.com/NordicPlayground)
- [nRF9160 DK Get Started](https://www.nordicsemi.com/Software-and-Tools/Development-Kits/nRF9160-DK/GetStarted#infotabs)
- [nRF Connect SDK Tutorial](https://devzone.nordicsemi.com/nordic/cellular-iot-guides/b/getting-started-cellular/posts/nrf-connect-sdk-tutorial)

