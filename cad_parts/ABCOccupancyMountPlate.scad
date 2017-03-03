$fa = 0.5;
$fs = 0.5;
$quality = 25;

plate_width = 60;
plate_height = 70;

mounting_hole_dia = 2.75;
mounting_hole_x_spacing = 45.8;
mounting_hole_y_spacing = 41.75;

pin_cutout_width = 40.3;
pin_cutout_height = 4;
pin_cutout_y_spacing = 19.5;
pin_cutout_row_spacing = 3.8;

board_cutout_width = 51;
board_cutout_height = 12.5;
board_cutout_y_spacing = 6.25;

plate_mount_dia = 3.25;
plate_mount_x_spacing = 6;
plate_mount_y_spacing = 6;

box_cutout_width = plate_width/2 + 10;
box_cutout_height = 15;
box_cutout_x_spacing = plate_width/2 + 2.5;
box_cutout_y_spacing = 7.75;

difference() {
    // plate itself
    square([plate_width, plate_height], r=3);
    
    // feather mounting holes
    translate([plate_width/2 - mounting_hole_x_spacing/2, plate_height/2 - mounting_hole_y_spacing/2])
        circle(mounting_hole_dia/2);
    translate([plate_width/2 + mounting_hole_x_spacing/2, plate_height/2 + mounting_hole_y_spacing/2])
        circle(mounting_hole_dia/2);
    translate([plate_width/2 - mounting_hole_x_spacing/2, plate_height/2 + mounting_hole_y_spacing/2])
        circle(mounting_hole_dia/2);
    translate([plate_width/2 + mounting_hole_x_spacing/2, plate_height/2 - mounting_hole_y_spacing/2])
        circle(mounting_hole_dia/2);
    
    // plate mounting holes
    translate([plate_mount_x_spacing, plate_mount_y_spacing])
        circle(plate_mount_dia/2);
    translate([plate_mount_x_spacing, plate_height - plate_mount_y_spacing])
        circle(plate_mount_dia/2);
    translate([plate_width - plate_mount_x_spacing, plate_mount_y_spacing])
        circle(plate_mount_dia/2);
    translate([plate_width - plate_mount_x_spacing, plate_height - plate_mount_y_spacing])
        circle(plate_mount_dia/2);
    
    // pin cutouts
    translate([(plate_width - pin_cutout_width)/2, plate_height/2 - mounting_hole_y_spacing/2 - pin_cutout_height])
        square([pin_cutout_width, pin_cutout_height]);
    translate([(plate_width - pin_cutout_width)/2, plate_height/2 + mounting_hole_y_spacing/2])
        square([pin_cutout_width, pin_cutout_height]);
    translate([(plate_width - pin_cutout_width)/2, plate_height/2 - pin_cutout_height])
        square([pin_cutout_width, pin_cutout_height*2]);
    
    // board cutouts
    translate([(plate_width - board_cutout_width)/2, plate_height/2 - board_cutout_height - board_cutout_y_spacing])
        square([board_cutout_width, board_cutout_height]);
    translate([(plate_width - board_cutout_width)/2, plate_height/2 + board_cutout_height - board_cutout_y_spacing])
        square([board_cutout_width, board_cutout_height]);

    // cutout for electrical box stuff
    translate([plate_width - box_cutout_x_spacing, plate_height - box_cutout_y_spacing])
        square([box_cutout_width, box_cutout_height]);
}