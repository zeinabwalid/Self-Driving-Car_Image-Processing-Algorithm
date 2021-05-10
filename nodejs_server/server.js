const express = require('express');
const app = express(); 
app.use(express.json());
const bodyParser= require('body-parser');
app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());

let Directions = [];
let RFIDs = [];


app.post('/sendDirection',(req,res)=>{ 
    Directions = [{
        Direction:req.body.Direction
    }];
    console.log(Directions);
    res.send(Directions);
     
});

app.get('/getDirection', (req, res) => {
         
    res.send(Directions);
    return Directions ;
    
});

app.post('/sendRFID',(req,res)=>{
    RFIDs = [{
        RFID:req.body.RFID
    }];
    res.send(RFIDs);
    console.log(RFIDs); 
});

app.get('/getRFID', (req, res) => { 
   
    res.send(RFIDs);
    return RFIDs;
});


const port = process.env.PORT ||80;
app.listen(80, () => console.log(`listening on port ${port}...`));