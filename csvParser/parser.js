
 var data;//idk premade variable

 var rawData;
 var datalog;
 var tempData;

 var final;

	 
	function handleFileSelect(evt) {
		var file = evt.target.files[0];
		console.log('changed!');
		Papa.parse(file, {
		  header: false,
		  dynamicTyping: true,
		  complete: function(results) {
			console.log("FINISHED PARSING!", results.data);
			//console.table(results.data);
			rawData = Array.from(results.data);
			//iterate thru all the data
				for (let index = 0; index < rawData.length; index++) {
					//iterate thru row values 
					for (let i = 0; i < array.length; i++) {
						
					}
				}	
				//console.log(final);
		  }
		});
	}
	

	//DATA, ERRORS ->  ARRAY OF FUCKEN ARRAYS
	//META -> OBJECT

	function DATA(id, time, DHTtemp, DHThum, BMPtemp, BMPpress, BMPalt, BMEtemp, BMEpress, BMEalt, BMEhum, yaw, pitch, roll){
		this.id = id;
		this.time= time;
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

	