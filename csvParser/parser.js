
 var data;//idk premade variable

 var rawData;
 var actualData;
 var finalData = {};
 var datalog;
	 
	function handleFileSelect(evt) {
		var file = evt.target.files[0];
		console.log('changed!');
		Papa.parse(file, {
		  header: false,
		  dynamicTyping: true,
		  complete: function(results) {
			console.log("FINISHED PARSING!", results.data);
			//console.table(results.data);
			rawData = results.data;

			//iterate thru result.data Array (which each element is array(1) as well)
			for (let index = 0; index < rawData.length; index++) {
				//console.log(rawData[index]);
				//rawData(1) array is stored as object, dunno why,should be array of rows, according to papa parse
				actualData = Array.from(rawData[index]);
				console.log(actualData);
			/*	for(var i = 0; i < actualData.length; i++){ 
					
				}*/

			}
			console.log(finalData);
		  }
		});
	}

	//DATA, ERRORS ->  ARRAY OF FUCKEN ARRAYS
	//META -> OBJECT

	function DATA(id, time, DHTtemp, DHThum, BMPtemp, BMPpress, BMPalt, BMEtemp, BMEpress, BMEalt, BMEhum, yaw, pitch, roll){
		this.id = id;
		this.time = time;
		this.DHTtemp = DHTtemp;
		this.DHThum = DHThum;
		this.BMPtemp = BMPtemp;
		this.BMPpress = BMPpress;
		this.BMPalt = BMPalt;
		this.BMEtemp = BMEtemp;
		this.BMEpress = BMEpress;
		this.BMEalt = BMEalt;
		this.BMEhum = BMEhum;
		this.yaw = yaw;
		this.pitch = pitch;
		this.roll = roll;
	}

	