var deg = 0;
var hum = 0;
var volt = 0;
var degK = "";
var humK = "";
var voltK = "";

function parseKeyValueString(str) 
{
    const pairs = str.split(';'); // Divide per coppie
    const result = {};
  
    pairs.forEach(pair => 
    {
        const [key, value] = pair.split(':'); // Divide chiave e valore
        if (key=='T')
        {
            degK = key;
            deg = value / 10
        }
        if (key=='H')
        {
            humK = key;
            hum = value / 1
        }
        if (key=='V')
        {
            voltK = key;
            volt = value / 100
        }  
        //result[key.trim()] = value.trim();    // Rimuove spazi e aggiunge all'oggetto
    });
    return;
}   

// Funzione di decodifica del payload per ChirpStack
function decodeUplink(input) {
    // Converti l'array di input bytes in una stringa rappresentativa
    let ascii = '';
    for (let i = 0; i < input.bytes.length; i++) {
        ascii += String.fromCharCode(input.bytes[i]);
    }
  	parsedData = parseKeyValueString(ascii);

    // Crea un oggetto JSON nidificato
    var nestedJson = {
        Temperature: {
            key: degK,
            value: deg
        },
        Humidity: {
            key: humK,
            value: hum
        },
        BattVoltage: {
            key: voltK,
            value: volt
        }
    };
    return {
        data: nestedJson,
        warnings: [],
        errors: []
    };
}