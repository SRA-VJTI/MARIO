let inpArray = document.querySelectorAll("input[type='text']");

//function to determine precision of rounding
            // const round = (number, decimalPlaces) => {
            //     const factorOfTen = Math.pow(10, decimalPlaces);
            //     return (Math.round(number * factorOfTen) / factorOfTen);
            // }
            // //function to convert radians to degrees
			
            // function radians_to_degrees(radians)
            // {
            // var pi = Math.PI;
            // return radians * (180/pi);
            // }

			function submitVals() {
				const data = {};


                  

				data["servo_a"] = parseFloat(document.getElementById("servo_a").value);
				data["servo_b"] = parseFloat(document.getElementById("servo_b").value);
				data["servo_c"] = parseFloat(document.getElementById("servo_c").value);
				
                // let res = inverseKinematics(data["servo_a"], data["servo_b"], data["servo_c"]);

                // console.log(res);
				// let joint = computeAngle(res);
				// data["servo_a"] = joint[0];
				// data["servo_b"] = joint[1];
				// data["servo_c"] = joint[2];
				// console.log(data);
				
                
                
                let finaldata = JSON.stringify(data);
				// console.log(finaldata);

				let xhr = new XMLHttpRequest();

				// Vedant!
				let url = "/api/v1/servo";

				// open a connection
				xhr.open("POST", url, true);

				// Set the request header i.e. which type of content you are sending
				xhr.setRequestHeader("Content-Type", "application/json");
				// Create a state change callback
				xhr.onreadystatechange = function () {
					if (xhr.readyState === 4) {
						if (xhr.status == 400) {
							console.log("Success!");
						} else {
							console.log(xhr.status);
						}
						// Print received data from server
					}
				};

				// Sending data with the request
				xhr.send(finaldata);
			}


			for (let i = 0; i < inpArray.length; i++) {
				inpArray[i].addEventListener("change", submitVals);
			}

			let decrementButtons = document.querySelectorAll(
				".button-group button:first-of-type"
			);
			let incrementButtons = document.querySelectorAll(
				".button-group button:last-of-type"
			);
			function decrementVal(e) {
				let test = e.target.parentNode.children[2].value;
				if (!isNaN(Number(test))) {
					e.target.parentNode.children[2].value = String(
						(Number(test) - 0.01).toFixed(3)
					);
					submitVals();
				} else {
					e.target.parentNode.children[2].value = "0.000";
				}
			}

			function incrementVal(e) {
				let test = e.target.parentNode.children[2].value;
				if (!isNaN(Number(test))) {
					e.target.parentNode.children[2].value = String(
						(Number(test) + 0.01).toFixed(3)
					);
					submitVals();
				} else {
					e.target.parentNode.children[2].value = "0.000";
				}
			}

			for (button of decrementButtons) {
				button.addEventListener("click", decrementVal);
			}
			for (button of incrementButtons) {
				button.addEventListener("click", incrementVal);
			}


            // function inverseKinematics(x, y, z) {
            //     //let servoa, servob, servoc;
            //     let result = [];
            //     var d0 = 2.5;    //Base to shoulder link length
    		//     var a1 = 12.0;   //Shoulder to elbow link length
	        //     var d3 = 9.5;    //Elbow to end effector link length
            //     const ROUNDING_ERROR = 10;
            //     let theta_base = round(Math.atan2(y,x), ROUNDING_ERROR);
            //     let theta_shoulder, theta_shoulder_possible, theta_elbow, theta_elbow_possible;
            //     sin_theta_elbow = round(((x * x + y * y + (z - d0) * (z - d0)) - a1 * a1 - d3 * d3) / (2 * a1 * d3), ROUNDING_ERROR)

            //     if(sin_theta_elbow <= 1 && (sin_theta_elbow) >= -1){
            //         theta_elbow = round(Math.asin(sin_theta_elbow), ROUNDING_ERROR);
            //         theta_elbow_possible = round(Math.PI - theta_elbow, ROUNDING_ERROR);

            //         let denominator = x*x + y*y + (z - d0) * (z - d0);

            //         if(theta_base != 90){
            //             let numerator_theta_shoulder = (z - d0)*(a1 + d3 * Math.sin(theta_elbow)) + d3 * Math.cos(theta_elbow)*x / Math.cos(theta_base);
                        
            //             let numerator_theta_shoulder_possible = (z - d0)*(a1 + d3*Math.sin(theta_elbow)) + d3*Math.cos(theta_elbow_possible) * x/ Math.cos(theta_base);

            //             theta_shoulder = round(Math.asin(numerator_theta_shoulder/denominator), ROUNDING_ERROR);
            //             theta_shoulder_possible = round(Math.asin(numerator_theta_shoulder_possible/denominator), ROUNDING_ERROR)
            //         }
            //         else if(theta_base != 0){
            //             let numerator_theta_shoulder = (z-d0)*(a1 + d3 * Math.sin(theta_elbow)) + d3*Math.cos(theta_elbow)* y/ Math.sin(theta_base);
            //             let numerator_theta_shoulder_possible = (z-d0)*(a1 + d3 * Math.sin(theta_elbow_possible)) + d3*Math.cos(theta_elbow_possible)* y/ Math.sin(theta_base);

            //             theta_shoulder = round(Math.asin(numerator_theta_shoulder / denominator), ROUNDING_ERROR);
            //             theta_shoulder_possible = round(Math.asin(numerator_theta_shoulder_possible / denominator), ROUNDING_ERROR);

            //         }

            //     }
            //     else{
            //         console.log("Point isn't in range due to constraints in link length");
            //         result = [null, null, null, null, null, null];
            //         return result;
            //     }
            //     result = [radians_to_degrees(theta_base), radians_to_degrees(theta_shoulder), radians_to_degrees(theta_elbow), radians_to_degrees(theta_base), radians_to_degrees(theta_shoulder_possible), radians_to_degrees(theta_elbow_possible)]; 
            //     return result;

            //     //let sin_theta_elbow = Math.round()
            //     // servo-c (theta-base) = tan^-1(y/z)
            //     // servo-b (theta-shoulder) = 
            //     // servo-c != 90 then servo-b = sin^-1((z-d0)*(a1+d3*sin(theta-elbow)) + d3*cos(theta-elbow)*x/cos(theta-base) / x^2 + y^2 + (z - d0)^2)
            //     // servo-c != 0 then servo-b = sin^-1((z-d0)*(a1+d3*sin(theta-elbow)) + d3*cos(theta-elbow)*y/sin(theta-base) / x^2 + y^2 + (z - d0)^2)
            //     // servo-a (theta-elbow) = sin^-1(x^2 + y^2 + (z - d0)^2 - a1^2 - d3^2 / 2*a1*d3)
            // }

			// function computeAngle(res)
			// {
			// 	let index =-1;
			// 	let count =0;
			// 	if (res[0] !=null && res[1]!=null && res[2]!=null)
			// 	{
			// 		if ( (0.0 <= res[0] && res[0] <= 180.0) && (0.0 <= res[1] && res[1] <= 180.0) && (0.0 <= res[2] && res[2] <= 180.0))
			// 		{
			// 			index =0;
			// 			count +=1;
			// 		}
			// 		if( (0.0 <= res[3] && res[3] <= 180.0) && (0.0 <= res[4] && res[4] <= 180.0) && (0.0 <= res[5] && res[5] <= 180.0))
			// 		{
			// 			index = 3;
			// 			count += 1;
			// 		}
			// 	}
			// 	if(index!= -1)
			// 	{
			// 		if(count ==2)
			// 		{
			// 			if (((res[1] + res[2]) % (2 * 180)) != 0 && (((res[1] + res[2]) % 180) == 0))
			// 			{
			// 				index = 0;
			// 			}
			// 			else if (((res[3] + res[4]) % (2 * 180)) != 0 && (((res[3] + res[4]) % 180) == 0))
			// 			{
			// 				index = 3;
			// 			}
			// 		}
			// 		let joint = [];
			// 		joint.push(res[index + 0]);
			// 		joint.push(res[index + 1]);
			// 		joint.push(res[index + 2]);

			// 		return joint;

			// 	}
			// 	else 
			// 	{
			// 		console.log("Invalid values");
			// 		return [null,null,null];
			// 	}
			// }


            
            
