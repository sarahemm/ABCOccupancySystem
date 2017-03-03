$fa = 0.5;
$fs = 0.5;
$quality = 25;

plate_width = 117.5;
plate_height = 117.5;

mounting_hole_dia = 4.5;
mounting_hole_x_spacing = 13.5;
mounting_hole_y_spacing = 17.5;

main_cutout_width = 77.5;
main_cutout_height = plate_height-6*2;
main_cutout_x_spacing = 20;
main_cutout_y_spacing = 6;

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
        
        // main cutout
        translate([main_cutout_x_spacing, main_cutout_y_spacing])
            square([main_cutout_width, main_cutout_height]);
        
        // switch leg cutouts
        translate([22,12])
            circle(9.8/2);
        translate([22,105.5])
            circle(9.8/2);
        
        // electronics cutout
        translate([87,26.5])
            square([20, 65]);
    }
}