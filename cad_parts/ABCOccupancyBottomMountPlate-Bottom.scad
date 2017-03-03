$fa = 0.5;
$fs = 0.5;
$quality = 25;

plate_width = 60;
plate_height = 70;

plate_mount_nut_width = 4;
plate_mount_nut_height = 3.45;
plate_mount_x_spacing = 6;
plate_mount_y_spacing = 6;

box_cutout_width = plate_width/2 + 10;
box_cutout_height = 15;
box_cutout_x_spacing = plate_width/2 + 2.5;
box_cutout_y_spacing = 7.75;

difference() {
    // plate itself
    square([plate_width, plate_height], r=3);
    
    // plate mounting nut holes
    translate([plate_mount_x_spacing, plate_mount_y_spacing]) {
        circle(plate_mount_nut_width/2, $fn=6);
        translate([-20, -plate_mount_nut_height/2])
            square([20, plate_mount_nut_height]);
    }
    translate([plate_mount_x_spacing, plate_height - plate_mount_y_spacing]) {
        circle(plate_mount_nut_width/2, $fn=6);
        translate([-20, -plate_mount_nut_height/2])
            square([20, plate_mount_nut_height]);
    }
    translate([plate_width - plate_mount_x_spacing, plate_mount_y_spacing]) {
        circle(plate_mount_nut_width/2, $fn=6);
        translate([0, -plate_mount_nut_height/2])
            square([20, plate_mount_nut_height]);
    }
    

    // cutout for electrical box stuff
    translate([plate_width - box_cutout_x_spacing, plate_height - box_cutout_y_spacing])
        square([box_cutout_width, box_cutout_height]);
}