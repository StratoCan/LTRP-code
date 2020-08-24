
 var data;//idk premade variable

 var actualData;
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
			actualData = results.data;

			for(x = 0; x < actualData.length; x++){
				actualData.forEach(stringToArray);
			}
			return datalog;

		  }
		});
	}

	function stringToArray(value){
		var splitted = value.split(",");
		datalog = new DATA(splitted);
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

	