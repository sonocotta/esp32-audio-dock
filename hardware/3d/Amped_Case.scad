$fn=200;

R=10;   //Kantenradius
W=3;    //Wand
HF=35; //Tiefe Oben
HR=55; //Tiefe Unten
X=95; //Breite Gehäuse
Y=70; //Höhe Gehäuse

text1="Amped";
text2="ESP32";



//Menü

part = 5; // [1:Housing, 2:Housing with Terminal 3:Front, 4:Clamp, 5:all]




//###########################################
if (part == 1){
    housing();
    };

if (part == 2){
    difference(){
    housing();
    terminal();
    
    }
    };
    
    
    if (part == 3) {
    rotate([180,0,0]) front();
    
    };
    //}
if (part == 4) {
    clamp();
    };
    
if (part == 5) {
    front();
    translate([0,0,5])clamp();
    translate([0,0,20])housing();
    
    };
   
 
//Gehäuse
module inner_housing(){

    hull(){
        translate([X/2,Y/2,R])sphere(r=R-W);
        translate([X/2,-Y/2,R])sphere(r=R-W);
        translate([-X/2,Y/2,R])sphere(r=R-W);
        translate([-X/2,-Y/2,R])sphere(r=R-W);

        translate([X/2,20,HR])sphere(r=R-W);
        translate([X/2,-Y/2,HF])sphere(r=R-W);
        translate([-X/2,20,HR])sphere(r=R-W);
        translate([-X/2,-Y/2,HF])sphere(r=R-W);
    }

}

module housing_neg() {
    difference(){
        translate([-(X+R*2)/2,-(Y+R*2)/2,+R])
        cube([X+R*2,Y+R*2,max(HF,HR)+R]);
        inner_housing();
    }
}

module display_neg() {
difference(){
    cube([X+R*2+5,Y+R*2+5,12],center=true);
    hull(){
        translate([X/2,Y/2,R])sphere(r=R);
        translate([X/2,-Y/2,R])sphere(r=R);
        translate([-X/2,Y/2,R])sphere(r=R);
        translate([-X/2,-Y/2,R])sphere(r=R);
}
translate([0,0,20])cube([150,150,20],center=true);
}
}

module gehaeuserand(){
translate([0,0,0]){
difference(){
hull(){
translate([X/2,Y/2,R])cylinder(r=R,h=2);
translate([X/2,-Y/2,R])cylinder(r=R,h=2);
translate([-X/2,Y/2,R])cylinder(r=R,h=2);
translate([-X/2,-Y/2,R])cylinder(r=R,h=2);
}


hull(){
translate([X/2,Y/2,R])cylinder(r=R-W/2,h=2);
translate([X/2,-Y/2,R])cylinder(r=R-W/2,h=2);
translate([-X/2,Y/2,R])cylinder(r=R-W/2,h=2);
translate([-X/2,-Y/2,R])cylinder(r=R-W/2,h=2);
}
}
}
}



module housing(){

difference(){
hull(){
translate([X/2,Y/2,R])sphere(r=R);
translate([X/2,-Y/2,R])sphere(r=R);
translate([-X/2,Y/2,R])sphere(r=R);
translate([-X/2,-Y/2,R])sphere(r=R);

translate([X/2,20,HR])sphere(r=R);
translate([X/2,-Y/2,HF])sphere(r=R);
translate([-X/2,20,HR])sphere(r=R);
translate([-X/2,-Y/2,HF])sphere(r=R);
}

inner_housing();

translate([X/2,Y/2,10]) cylinder(d=3.5,h=35);
translate([X/2,-Y/2,10]) cylinder(d=3.5,h=35);
translate([-X/2,Y/2,10]) cylinder(d=3.5,h=35);
translate([-X/2,-Y/2,10]) cylinder(d=3.5,h=35);

translate([X/2,Y/2,15]) cylinder(d=6,h=35);
translate([X/2,-Y/2,15]) cylinder(d=6,h=35);
translate([-X/2,Y/2,15]) cylinder(d=6,h=35);
translate([-X/2,-Y/2,15]) cylinder(d=6,h=35);

//Schnitt
translate([0,0,0])cube([X+50,150,20],center=true);

//Netzteilstecker
translate([40,-19.5,10])rotate([0,90,0])cylinder (d=8.5,h=30);

gehaeuserand();
}


//Führungsrohre für Schrauben
difference(){
union(){
translate([X/2,Y/2,11]) cylinder(d=R+W+2,h=HF+15);
translate([X/2,-Y/2,11]) cylinder(d=R+W+2,h=HF+15);
translate([-X/2,Y/2,11]) cylinder(d=R+W+2,h=HF+15);
translate([-X/2,-Y/2,11]) cylinder(d=R+W+2,h=HF+15);
}
translate([X/2,Y/2,10]) cylinder(d=3.5,h=HF);
translate([X/2,-Y/2,10]) cylinder(d=3.5,h=HF);
translate([-X/2,Y/2,10]) cylinder(d=3.5,h=HF);
translate([-X/2,-Y/2,10]) cylinder(d=3.5,h=HF);




housing_neg();

translate([X/2,Y/2,15]) cylinder(d=6.5,h=35);
translate([X/2,-Y/2,15]) cylinder(d=6.5,h=35);
translate([-X/2,Y/2,15]) cylinder(d=6.5,h=35);
translate([-X/2,-Y/2,15]) cylinder(d=6.5,h=35);

}
}

module terminal(){
translate([5,0,0]){
union(){
//Ausschnitt Lautsprecher-Terminal
translate([-5,5,HR]) rotate([-70,0,0]) cube([51,30, 20],center=true);

//Verschraubung Terminal

translate([25,6.5,HR])rotate([30,0,0])cylinder (d=4,h=100);
translate([-35,6.5,HR])rotate([30,0,0])cylinder (d=4,h=100);
}
}
}



module front(){


translate([8,-4,3])rotate([180,0,0])linear_extrude(4)
    text(text1, font = "Liberation Sans", size = 7);    
    
translate([8,7,3])rotate([180,0,0])linear_extrude(4)
    text(text2, font = "Liberation Sans", size = 7);
//Zylinder für Boardbefestigung



difference(){
union(){
translate([-39,24.5,W])cylinder(d=8,h=12);
translate([19,-24.5,W])cylinder(d=8,h=12);
translate([-39,-24.5,W])cylinder(d=8,h=12);
}

translate([-39,24.5,W])threads(diameter=3, pitch=0.5, length=13, rez=60);
translate([19,-24.5,W])threads(diameter=3, pitch=0.5, length=13, rez=60);
translate([-39,-24.5,W])threads(diameter=3, pitch=0.5, length=13, rez=60);

translate([-36.5,19.5,10])cube([3,10,6]);

}

difference(){
gehaeuserand();
//Netzteilstecker
translate([40,-19.5,10])rotate([0,90,0])cylinder (d=8.5,h=30);
//Displayfront
}
difference(){

hull(){
translate([X/2,Y/2,R])sphere(r=R);
translate([X/2,-Y/2,R])sphere(r=R);
translate([-X/2,Y/2,R])sphere(r=R);
translate([-X/2,-Y/2,R])sphere(r=R);
}

hull(){
translate([X/2,Y/2,R])sphere(r=R-W);
translate([X/2,-Y/2,R])sphere(r=R-W);
translate([-X/2,Y/2,R])sphere(r=R-W);
translate([-X/2,-Y/2,R])sphere(r=R-W);
}


translate([0,0,20])cube([150,150,20],center=true);

//Display
translate([-25,0,-2]) cube([32,16.5, 20],center=true);
translate([-25,-2,6]) cube([35.5,23, 10],center=true);

//Netzteilstecker
translate([40,-19.5,10])rotate([0,90,0])cylinder (d=8.5,h=30);

//IR-Sensor
translate([-18,25,1])cylinder(d=15,h=5);

}



//Rahmen

difference(){
union(){
translate([-50,0,W-0.1])cylinder(d=6,h=4);
translate([0,0,W-0.1])cylinder(d=6,h=4);
translate([-25,14,W-0.1])cylinder(d=6,h=4);
}
translate([-25,0,3]) cube([45.5,26, 2.3],center=true);
display_neg();
}


difference(){
union(){
translate([X/2,Y/2,W/2]) cylinder(d=10,h=8.5);
translate([X/2,-Y/2,W/2]) cylinder(d=10,h=8.5);
translate([-X/2,Y/2,W/2]) cylinder(d=10,h=8);
translate([-X/2,-Y/2,W/2]) cylinder(d=10,h=8);

}



translate([X/2,Y/2,W/2])threads(diameter=3, pitch=0.5, length=13, rez=60);
translate([X/2,-Y/2,W/2])threads(diameter=3, pitch=0.5, length=13, rez=60);
translate([-X/2,Y/2,W/2])threads(diameter=3, pitch=0.5, length=13, rez=60);
translate([-X/2,-Y/2,W/2])threads(diameter=3, pitch=0.5, length=13, rez=60);


}



}


module clamp(){
difference(){
hull(){
translate([-25,0,5]) cube([45,30, 0.1],center=true);
translate([-25,0,6.9]) cube([41,26, 0.1],center=true);
}
translate([-25,0,5]) cube([32,20, 10],center=true);
translate([-25,-5,5]) cube([20,20, 10],center=true);
}
}


module threads(diameter=4,pitch=undef,length=10,scale=1,rez=20){
	pitch = (pitch!=undef) ? pitch : get_coarse_pitch(diameter);
	twist = length/pitch*360;
	depth=pitch*.6;
	linear_extrude(height = length, center = false, convexity = 10, twist = -twist, $fn = rez)
		translate([depth/2, 0, 0]){
			circle(r = scale*diameter/2-depth/2);
		}
}