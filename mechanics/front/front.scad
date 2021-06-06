tolerance = 0.5;
front_width = 483;
front_height = 3*44.45;
thickness = 3;
pouce = 25.4;

module xlr(thickness, tolerance) {
	mount_diam = 3.5;
	bbox_height = 35.55;
	bbox_width = 26.2;
	diam = 21.3;
	notch_width = 10.2 + tolerance;
	notch_height = 22.2 - diam + tolerance;
	cylinder(thickness, (diam + tolerance) / 2, (diam + tolerance) / 2);
	translate([-notch_width/2, 0, 0]) {
		cube(size=[notch_width, diam / 2 + notch_height, thickness]);
	}
	translate([-(bbox_width / 2 - 5), (bbox_height / 2 - 5), 0]) {
		cylinder(thickness, mount_diam / 2, mount_diam / 2);
	}
	translate([(bbox_width / 2 - 5), -(bbox_height / 2 - 5), 0]) {
		cylinder(thickness, mount_diam / 2, mount_diam / 2);
	}
}

module power(thickness, tolerance) {
	diam = 19.3;
	notch_width = 6 + tolerance;
	notch_height = 21.5 - diam + tolerance;
	cylinder(thickness, (diam + tolerance) / 2, (diam + tolerance) / 2);
	translate([-notch_width/2, 0, 0]) {
		cube(size=[notch_width, diam / 2 + notch_height, thickness]);
	}
}

module screen(width, height, thickness, tolerance) {
	translate([-tolerance/2, tolerance/2, 0]) {
		cube(size=[width+tolerance, height+tolerance, thickness]);
	}
	translate([5, -5, 0]) {
		cylinder(thickness, 1.5 + tolerance/2, 1.5 + tolerance / 2);
	}
	translate([width - 5, -5, 0]) {
		cylinder(thickness, 1.5 + tolerance/2, 1.5 + tolerance / 2);
	}
	translate([5, height + 5, 0]) {
		cylinder(thickness, 1.5 + tolerance/2, 1.5 + tolerance / 2);
	}
	translate([width - 5, height + 5, 0]) {
		cylinder(thickness, 1.5 + tolerance/2, 1.5 + tolerance / 2);
	}
}

projection() {
	difference() {
		// Front
		cube(size=[front_width, front_height, thickness]);
		// Fixing screws
		translate([32.5, 18.5, -thickness]) {
			cylinder(3*thickness, 2.5 + tolerance / 2, 2.5 + tolerance / 2);
		}
		translate([32.5, front_height - 18.5, -thickness]) {
			cylinder(3*thickness, 2.5 + tolerance / 2, 2.5 + tolerance / 2);
		}
		translate([front_width - 32.5, 18.5, -thickness]) {
			cylinder(3*thickness, 2.5 + tolerance / 2, 2.5 + tolerance / 2);
		}
		translate([front_width - 32.5, front_height - 18.5, -thickness]) {
			cylinder(3*thickness, 2.5 + tolerance / 2, 2.5 + tolerance / 2);
		}
		// Handle screws
		translate([3*pouce/8, 3*pouce/2, -thickness]) {
			cylinder(3*thickness, pouce/8, pouce/8);
		}
		translate([3*pouce/8, front_height - 3*pouce/2, -thickness]) {
			cylinder(3*thickness, pouce/8, pouce/8);
		}
		translate([front_width - 3*pouce/8, 3*pouce/2, -thickness]) {
			cylinder(3*thickness, pouce/8, pouce/8);
		}
		translate([front_width - 3*pouce/8, front_height - 3*pouce/2, -thickness]) {
			cylinder(3*thickness, pouce/8, pouce/8);
		}
		// Screen
		translate([80, 80, -thickness]) {
			screen(130, 32, 3*thickness, tolerance);
		}
		// XLR
		translate([90, 35, -thickness]) {
			xlr(3*thickness, tolerance);
		}
		// Rotary Encoder
		translate([145, 35, -thickness]) {
			cylinder(3*thickness, (7+tolerance)/2, (7+tolerance)/2);
		}
		// Gaz out
		translate([200.0, 35, -thickness]) {
			cylinder(3*thickness, (12+tolerance)/2, (12+tolerance)/2);
		}
		// Gaz in
		translate([250, 35, -thickness]) {
			cylinder(3*thickness, (17+tolerance)/2, (17+tolerance)/2);
		}
		// Power In+
		translate([front_width-170, 35, -thickness]) {
			power(3*thickness, tolerance);
		}
		// Power In-
		translate([front_width-170, front_height-35, -thickness]) {
			power(3*thickness, tolerance);
		}
		// Power Out+
		translate([front_width-80, 35, -thickness]) {
			power(3*thickness, tolerance);
		}
		// Power Out-
		translate([front_width-80, front_height-35, -thickness]) {
			power(3*thickness, tolerance);
		}
	}
}
