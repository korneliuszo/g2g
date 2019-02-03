
include <toothedLinearBearing.scad>
 
union(){
difference(){
    union(){
        translate([0,0,2.5])
            cube([46,50,5],true);
        translate([0,20,-10])
            cube([46,10,20],true);
        translate([0,-20,-10])
            cube([46,10,20],true);
    }
    translate([0,-20,-2])
        rotate([90,0,0])
    union(){
        cylinder(41,d=3.9,center=true);
        cylinder(4,d=6.65,center=true,$fn=6);
    }
    translate([-13,0,-10])
        rotate([90,0,0])
        cylinder(51,d=12,center=true);
    translate([13,0,-10])
        rotate([90,0,0])
        cylinder(51,d=12,center=true);
}
}