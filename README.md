# CS580S_Group_08_Project
CIS 4360 Seminar on Topics in CS/Smart Sensing and Devices (Fall 2024)

Link To Live Demo: https://drive.google.com/file/d/1aZzy3g-ZEYuLYoqfQ9pEFobpRVai_FGK/view?usp=sharing 


All the Action Messages:


 soilLevel == "LOW" && humidity >= 30 && humidity <= 60


 
 "Water Now"


 
 soilLevel == "MED" && humidity >= 30 && humidity <= 60


 
 "Water & Air OK"

 
 soilLevel == "HIGH" && humidity >= 30 && humidity <= 60

 
 "Don't Water";

 
 soilLevel == "LOW" && humidity < 30 || humidity > 60

 
 "Water & Move"

 
 soilLevel == "MED" && humidity < 30 || humidity > 60

 
 "Move Plant"

 
 soilLevel == "HIGH" && humidity < 30 || humidity > 60




 
 "Don't Water&Move"
