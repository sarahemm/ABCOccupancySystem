$fa = 0.5;
$fs = 0.5;
$quality = 25;

plate_width = 117.5;
plate_height = 117.5;

mounting_hole_dia = 4.5;
mounting_hole_x_spacing = 13.5;
mounting_hole_y_spacing = 17.5;

switch_cutout_width = 11;
switch_cutout_height = 24;
switch_cutout_x_spacing = 30;
switch_cutout_y_spacing = 46.5;

disp_cutout_width = 28;
disp_cutout_height = 11;
disp_cutout_x_spacing = 65;
disp_cutout_y_spacing = 70;

led_cutout_width = 40;
led_cutout_height = 20;
led_cutout_x_spacing = 57;
led_cutout_y_spacing = 41;

difference() {
    // plate itself
    square([plate_width, plate_height], r=4);
    
    union() {
        // mounting holes
        translate([mounting_hole_x_spacing, mounting_hole_y_spacing])
            circle(mounting_hole_dia/2);
        translate([mounting_hole_x_spacing, plate_height-mounting_hole_y_spacing])
            circle(mounting_hole_dia/2);
        translate([plate_width-mounting_hole_x_spacing, mounting_hole_y_spacing])
            circle(mounting_hole_dia/2);
        translate([plate_width-mounting_hole_x_spacing, plate_height-mounting_hole_y_spacing])
            circle(mounting_hole_dia/2);
        
        // switch cutout
        translate([switch_cutout_x_spacing, switch_cutout_y_spacing])
            square([switch_cutout_width, switch_cutout_height]);

        // display cutout
        translate([disp_cutout_x_spacing, disp_cutout_y_spacing])
            square([disp_cutout_width, disp_cutout_height]);

        // LED cutout
        translate([led_cutout_x_spacing, led_cutout_y_spacing])
            square([led_cutout_width, led_cutout_height], r=1);
    }
}