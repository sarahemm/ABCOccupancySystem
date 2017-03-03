$fa = 0.5;
$fs = 0.5;
$quality = 25;

plate_width = 60;
plate_height = 70;

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
        
    // plate mounting holes
    translate([plate_mount_x_spacing, plate_mount_y_spacing])
        circle(plate_mount_dia/2);
    translate([plate_mount_x_spacing, plate_height - plate_mount_y_spacing])
        circle(plate_mount_dia/2);
    translate([plate_width - plate_mount_x_spacing, plate_mount_y_spacing])
        circle(plate_mount_dia/2);
    translate([plate_width - plate_mount_x_spacing, plate_height - plate_mount_y_spacing])
        circle(plate_mount_dia/2);
    
    // cutout for electrical box stuff
    translate([plate_width - box_cutout_x_spacing, plate_height - box_cutout_y_spacing])
        square([box_cutout_width, box_cutout_height]);
}