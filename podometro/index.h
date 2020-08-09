const char page[] PROGMEM= R"=====(
<!doctype html>
<html lang="it">
  <meta http-equiv="Refresh" content="30">
<head>
    <title>Podometro</title>
    <link rel="stylesheet" href="stili.css" type="text/css" />
    <style></style>


  
    
</head>
   
<body>
    <script>
       
    
    var url = "DATA.txt";

var request = new XMLHttpRequest();  
request.open("GET", url, false);   
request.send(null);  

var csvData = new Array();
var jsonObject = request.responseText.split(/\r?\n|\r/);
for (var i = 0; i < jsonObject.length; i++) {
  csvData.push(jsonObject[i].split(','));
    
}
        csvData.pop();
        csvData.push(["","0","0"]);
       
   

    
function getMedia(day){
     
    
    var i=1;
    var pesotot= Array.apply(null, new Array(6)).map(Number.prototype.valueOf,0); 
    var pesomedia= Array.apply(null, new Array(6)).map(Number.prototype.valueOf,0);

    
    while(csvData[i][0]!=day && csvData[i][0]!="")
         i++;
    var numEl=i;
    if(csvData[i]==""){
        console.log("error:no-record");
        return;
    }
  
    while(csvData[i][0]==day && csvData[i][0]!=""){
        pesotot[0]+=Number(csvData[i][2]);
        pesotot[1]+=Number(csvData[i][3]);
        pesotot[2]+=Number(csvData[i][4]);
        pesotot[3]+=Number(csvData[i][5]);
        pesotot[4]+=Number(csvData[i][6]);
        pesotot[5]+=Number(csvData[i][7]);
       
        i++;
        
    }


    pesomedia[0]=pesotot[0]/(i-numEl);
    pesomedia[1]=pesotot[1]/(i-numEl);
    pesomedia[2]=pesotot[2]/(i-numEl);
    pesomedia[3]=pesotot[3]/(i-numEl);
    pesomedia[4]=pesotot[4]/(i-numEl); 
    pesomedia[5]=pesotot[5]/(i-numEl); 
   
    var i=0;
    for(i=0;i<6;i++){
        col(pesomedia[i],i+1);
        
        
    }
   
}

    
function col(peso,i){ 
 var RC=0;
 var GC=0;
 var BC=0;
var normPeso=0;
 element=document.getElementById("cerchio"+i);
element2=document.getElementById("cerchior"+i);
     if(peso<=5000){
         BC=255;
         GC=peso/19.6;
         RC=0;
     }
     if(peso>5000 && peso<=10000){
       normpeso=map(peso,5000,10000,255,0);
        RC=0;
        GC=255;
        BC=normpeso;
     }
     if(peso>10000 && peso<=15000){
         normpeso=map(peso,10000,15000,0,255);
         RC=normpeso;
         GC=255;
         BC=0;
     }
     if(peso>15000 && peso<=20000){
         normpeso=map(peso,15000,20000,255,0);
         RC=255;
         GC=normpeso;
         BC=0;
     }
     element.setAttribute("style", "background-color:rgb("+RC+","+GC+","+BC+")");
    element2.setAttribute("style", "background-color:rgb("+RC+","+GC+","+BC+")");

 }

        
function map(value,min,max,nmin,nmax){
    value=(((value-min)/(max-min))*(nmax-nmin))+nmin;
    return value;
}
        
        
function getWeekActivity(day){
     var i=1;
     while(csvData[i][0]!=day && csvData[i][0]!="")
         i++;

    if(csvData[i][0]==""){
        console.log("error:no-record");
        return;
    }
  
    while(csvData[i][0]==day && csvData[i][0]!="")
        i++;
    i--;
    
    document.getElementById("passi").innerHTML = csvData[i][1];
    document.getElementById("km").innerHTML = (csvData[i][1]*0.00074).toFixed(2);
  document.getElementById("cal").innerHTML =       (csvData[i][1]*0.00074*70).toFixed(2);
    
    
    
    
}
    
    
function getActivity(){
    document.getElementById("passiG").innerHTML = csvData[csvData.length-3][1];
    document.getElementById("kmG").innerHTML = (csvData[csvData.length-3][1]*0.00074).toFixed(2);
    document.getElementById("calG").innerHTML = (csvData[csvData.length-3][1]*0.00074*70).toFixed(2);
    
}   
    

    
    </script>
    
    <br>
       <div id="container">
         
        <div id="statg">
        <br><br><br><br><br><br><br>
        <h2 onclick="getActivity()" id="aggiorna">Attivit�</h2>
        <br><br><br><br>
        <table>
        <tr><td >Passi</td> <td>Km</td> <td>Cal</td> </tr>
        <tr><td id="passiG"></td> <td id="kmG"></td> <td id="calG"></td> </tr>
        </table>
        </div>     
        
        <div id="stats">
        <br>
        <h2 >Attivit� giornaliera</h2>
        <br><br>       
        <table>
             <tr><td class="statse" > <a  onclick="getWeekActivity(0)">Lu</a></td> <td class="statse" > <a  onclick="getWeekActivity(1)">Ma</a> </td> <td class="statse"> <a  onclick="getWeekActivity(2)">Me</a> </td> <td class="statse">  <a  onclick="getWeekActivity(3)">Gi</a> </td> <td class="statse"> <a  onclick="getWeekActivity(4)">Ve</a></td> <td class="statse"><a  onclick="getWeekActivity(5)">Sa</a></td> <td class="statse"><a  onclick="getWeekActivity(6)">Do</a></td> </tr>
        </table>
        <br><br><br><br><br><br>
        <table>
        <tr><td>Passi</td> <td>km</td> <td>Cal</td> </tr>
         <tr><td id="passi"></td> <td id="km"></td> <td id="cal"></td> </tr>
        </table>
        </div>              
           
         <div id="piedis">
            <div id="cerchio1" class="circlea"></div>
            <div id="cerchio2" class="circlec"></div>
            <div id="cerchio3" class="circled"></div>
            <div id="cerchio4" class="circlee"></div>
            <div id="cerchio5" class="circlef"></div>
            <div id="cerchio6" class="circleh"></div>
            
            <div id="cerchior1" class="circlera"></div>
            <div id="cerchior2" class="circlerc"></div>
            <div id="cerchior3" class="circlerd"></div>
            <div id="cerchior4" class="circlere"></div>
            <div id="cerchior5" class="circlerf"></div>
            <div id="cerchior6" class="circlerh"></div>
        <br>
        <h2 >Riepilogo settimanale</h2>
            
        <table>
            <tr><td class="sett" > <a  onclick="getMedia(0)">Lu</a></td> </tr>
            <tr><td class="sett"> <a  onclick="getMedia(1)">Ma</a> </td> </tr>
            <tr><td class="sett"> <a  onclick="getMedia(2)">Me</a> </td> </tr>
            <tr><td class="sett">  <a  onclick="getMedia(3)">Gi</a> </td> </tr>
            <tr><td class="sett"> <a  onclick="getMedia(4)">Ve</a></td> </tr>
            <tr><td class="sett"><a  onclick="getMedia(5)">Sa</a></td> </tr>
            <tr><td class="sett"><a  onclick="getMedia(6)">Do</a></td> </tr>
            
        </table> 
           <table>
        <tr margin-left="60px"; margin-right="50px";><td class="piedi1"; style="text-align:right;">0 kg</td><td class="piedi1">5 kg</td><td class="piedi1">10 kg</td><td class="piedi1">15 kg</td><td class="piedi1"; style="text-align:left;">20 kg</td></tr>    
        </table> 
        </div>
           
        <div id="link">
           <h2><a id="sott" href="/Scansione">Scansione pressione</a></h2>
            
           </div>
           
    </div>
    
</body>
</html>
 )=====";
 
 
 
 
 const char sendTemplate[] PROGMEM= R"=====(@@peso1@@
@@peso2@@
@@peso3@@
@@peso4@@
@@peso5@@
@@peso6@@
 )=====";
 
 
 
 
 
 
 const char scansione[] PROGMEM= R"=====( 

<!doctype html>
<html lang="it">
   
<head>
    <title>Scansione Podometro</title>
    <link rel="stylesheet" href="stili.css" type="text/css" />
    <style></style>

<script>
window.onload=setInterval("loadDoc()", 500);
        
function col(peso,i){ 
 	var RC=0;
 	var GC=0;
 	var BC=0;
	var normPeso=0;
 	element=document.getElementById("cerchio"+i);
	element2=document.getElementById("cerchior"+i);
	
     if(peso<=5000){
         BC=255;
         GC=peso/19.6;
         RC=0;
     }
     if(peso>5000 && peso<=10000){
       normpeso=map(peso,5000,10000,255,0);
        RC=0;
        GC=255;
        BC=normpeso;
     }
     if(peso>10000 && peso<=15000){
         normpeso=map(peso,10000,15000,0,255);
         RC=normpeso;
         GC=255;
         BC=0;
     }
     if(peso>15000 && peso<=20000){
         normpeso=map(peso,15000,20000,255,0);
         RC=255;
         GC=normpeso;
         BC=0;
     }
     element.setAttribute("style", "background-color:rgb("+RC+","+GC+","+BC+")");
     element2.setAttribute("style", "background-color:rgb("+RC+","+GC+","+BC+")");

 }

                
function map(value,min,max,nmin,nmax){
    value=(((value-min)/(max-min))*(nmax-nmin))+nmin;
    return value;
}
        
</script>
    
    
</head>
    
    <body id="Scan" >    
         <br>
       <div id="containerScan">

         <div id="piedig">
             
            <div id="cerchio1" class="circlea"></div>
            <div id="cerchio2" class="circlec"></div>
            <div id="cerchio3" class="circled"></div>
            <div id="cerchio4" class="circlee"></div>
            <div id="cerchio5" class="circlef"></div>
            <div id="cerchio6" class="circleh"></div>
            
            <div id="cerchior1" class="circlera"></div>
            <div id="cerchior2" class="circlerc"></div>
            <div id="cerchior3" class="circlerd"></div>
            <div id="cerchior4" class="circlere"></div>
            <div id="cerchior5" class="circlerf"></div>
            <div id="cerchior6" class="circlerh"></div>
             
			<h2 >Esame in tempo reale</h2>
			<br><br><br><br><br><br><br><br><br><br><br><br><br>
			<table>
    			<tr margin-left="60px"; margin-right="50px";><td class="piedi1"; style="text-align:right;">0 kg</td><td class="piedi1">5 kg</td><td class="piedi1">10 kg</td><td class="piedi1">15 kg</td><td class="piedi1"; style="text-align:left;">20 kg</td></tr>    
			</table>
</div>
           
<div id="link">
    <h2><a id="sott" href="/">Torna indietro</a></h2> 
</div>
        
</div>
        
<script>
           
    function loadDoc() {
        
        
    var xhttp = new XMLHttpRequest();
        
    xhttp.onreadystatechange = function support() {
        
        if (this.readyState == 4 && this.status == 200) {
        var pressione=new Array;
            var xmlObject = xhttp.responseText.split(/\r?\n|\r/)
         
            for (var i = 0; i <= xmlObject.length; i++) {
                pressione.push(xmlObject[i]);
            }
            

    for(var j=0;j<6;j++){
        col(pressione[j],j+1);
    }
}

    };
    xhttp.open("GET", "\Up", true);
    xhttp.send();
}
    
    
        </script>
        
</body>
 )=====";
