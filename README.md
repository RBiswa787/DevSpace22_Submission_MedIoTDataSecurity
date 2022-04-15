# DevSpace22_Submission_MedIoTDataSecurity
## Problem Statement
“More than 60% of India’s population lives in rural India while only 40% of healthcare providers work here. According to one report there is 83% shortfall of physicians in community health centres in rural areas.” - Dr. Yogesh Kalkonde.

Present solutions being developed include IoT based remote health monitoring systems connecting rural people to doctors in urban centres. However, the security of patient data generated and stored by these systems is questionable. Also, such data is highly valuable in clinical research but at the same time is difficult to procure, considering benefits of private data and risks of exposing it.

## Solution
Our solution is to develop an IoT based remote health monitoring system that:
1. Collects vitals of patient
2. Uploads real time sensor readings to the cloud
3. Doctor can access the data through a temporary token based access protocol (patient consent required)
4. (With prior consent from patient) anonymous clinical data is published as NFTs on Ocean Protocol (for use in clinical research)
5. Patients contributing to clinical research are incentivised

## Explanation
How it works?
The remote health monitoring system authenticates a patient using fingerprint scanner. Sensors collect vital signs of patient and uploads data to cloud database in encrypted form. On appointment, doctor requests for patient data for diagnosis, patient gives consent by fingerprint. Doctor gets a token to temporarily access the patient health records. 
If patient gives consent for his/her health records being used for clinical research. The data is uploaded to Ocean Protocol and patient is incentivised. Data is securely stored in decentralised storage of Ocean Protocol. Research organisations can select one or more algorithms to run on patient health records. Instead of providing access to the data directly, Ocean Compute to Data runs the requested algorithms on the data inside Ocean Ecosystem and returns the results to the research organisation in exchange of 1.0 data token. 
