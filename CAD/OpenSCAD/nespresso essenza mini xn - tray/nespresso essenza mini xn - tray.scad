// Depth (X), Width (Y), Height (Z)
// Viewperspective, at front
/*[ Tray ]*/
// Draw the tray
drawTray = true;
// Thickness of tray walls/bottom
trayWall = 2; //[2:8]
// Width of tray
trayWidth = 69; //[20:120]
// Height of tray
trayHeight = 25; //[8:39]
//(Minimal) Distance from case to center of the cup "circle"
cupLength = 58; //[30:80]

/*[ Lid ]*/
//Draw the lid
drawLid = true;
// Distance between puncture holes in tray lid
holesDistance = 7.3; //[6.5:0.1:10]

/*[ Debug ]*/
// Show description of used colors/objects
showColorDescription = false;


/* [Hidden] */
depth=0;
width=1;
height=2;

backWidth = 69;
backHeight = 33;

safeCut=100; // A(ny) big number

cutMinimalMargin = $preview ? 0.01 : 0;

caseDepth = 13; //Tray moves this, into the casing
lowerEdge = 6; // At bottom, small threshold from floor/outside when "entering" casing
lowerEdgeSafe = lowerEdge + trayWall; // Covering the threshold, minimal height


backconnectionBlock = [5, 48, 28]; // Big cut-out at the back
backconnectionBlockEdge = [3, 48, 35]; // Extende spare-out in big cut-out at the back
backconnectionBlockEdgeNudge = [backconnectionBlock[depth],2,35]; // And finally the small spare-out

lidThick = trayWall;


backBlockDepth=10;
backblock = [backBlockDepth, backWidth, backHeight]; //Part that hooks on the cups bin
backrise = [caseDepth, backWidth, lowerEdge]; // "Negative" Space required for slide into coffee machine
// A (minimal) block on top of the rise/threshold,
// to ensure proper connection between tray and back
backriseBlock = [backBlockDepth, backWidth, lowerEdgeSafe];

maincup = [
    cupLength-backBlockDepth,
    // Main (square) body, never wider then backblock
    trayWidth > backblock[width] ? backblock[width] : trayWidth,
    trayHeight
];

/*
* Actual coding

    The "tray_cup" shape is a re-occuring shape;
    Used for:
    - Tray cup (duh ;-), solid
    - Tray cup cut-out; logical difference with a smaller tray cup
    - Tray cup lid; tray cup solid, with small height
    - Tray cup lid, snap fit; even smaller tray cup solid, with small height
*/


if($preview && showColorDescription) {
    // Show color (coded legenda) building blocks
    legenda = [
        "red", "(cut) Backfit, safety cutouts for fitting into machine"
        ,"Magenta", "Tray back, where tray hooks onto cups bin in machine"
        ,"Lime", "Tray cup solid"
        ,"Green", "(cut) Tray cup carve out"
        ,"Indigo", "(cut) Carve out from bottom 'outside', so the cup is not flat"
        ,"Cyan", "Tray Lid"
        // ,"Orange", "Orange"
        // ,"Crimson", "Crimson"
        // ,"Tomato","Tomato"
        // ,"Chocolate", "Chocolate"
        // ,"Olive", "Olive"
        // ,"DarkCyan", "DarkCyan"
        // ,"blue", "is blue"
        // ,"Navy", "Navy"
        // ,"SkyBlue", "SkyBlue"
    ];
    legenda_fontsize = 10;

    translate([tray_circle_center_x()+trayWidth/2,0,0])   rotate(a = 90) 
    for (i = [ 0 : 2: len(legenda) - 1 ]) { translate([0,-(legenda_fontsize*1.2*(i+1)),0]) color(legenda[i]) text(text=legenda[i+1], size=legenda_fontsize); }
}


if($preview){
    $fn=10;
} else {
    $fn=100;
}

if (drawTray) {
    difference() // Cut, bottum up, and finally the rest so it fits
    {
        union(){ // Closure tray back (lower) edge
            difference() { // tray carve-out
                union() // Back and tray
                {
                    tray_back(colored="Magenta");    // Tray back solid
                    cube([ backrise[depth]+trayWall, backrise[width], backrise[height]+trayWall ]); // Edge to ground, just within the case

                    tray_cup(colored="Lime", cupHeight= maincup[height]);  // Tray cup  solid
                }
                // Carve out the tray cup
                tray_cup_carve(wallThickness=trayWall, colored="Green",cupHeight= maincup[height]);
            }
            cube([ backrise[depth]+trayWall, backrise[width], backrise[height]+trayWall ]); // Closure for Edge to ground, just within the case
        }
        // Carve out from bottom "outside", so the cup is not flat (on a flat surface will "suck" liquids and generate stains...)
        translate([0,0,-1])
            tray_cup(wallThickness=trayWall,colored="Indigo", cupHeight=  1+trayWall*1.5);

        backfit(colored="red");                                              // Carve out back fit (into machine)
    }
}

if(drawLid) {
    tray_cup_lid(colored="Cyan");
}

module tray_cup_lid(wallThickness = 0, colored="#03FC30"){
    difference() 
    {
        union() {
            // tray_cup(lid = true, colored=colored);
            translate([0,0,maincup[height]]) // Place lid on tray cup
                tray_cup(lid = true, colored=colored, cupHeight=lidThick);

            translate([0,0,maincup[height]+trayWall]) // Place snapfit on top of lid, for viewing purpose
                tray_cup_lid_edge(wallThickness=trayWall);
        }


        translate([0,0,-safeCut/2]) scale(v = [1,1,safeCut])
        {
            
            intersection() 
            {
            // Punch holes in the lid
            translate([tray_circle_center_x(),backWidth/2,maincup[height]]) 
                holes(height=safeCut, r_limit=cupLength, distance=holesDistance);
            tray_cup_lid_edge(wallThickness=trayWall);

            }
        }
    }
}
module tray_cup_lid_edge(wallThickness = 0, colored="#03FC30"){
        tray_cup(wallThickness = wallThickness, lid = true, colored=colored, cupHeight=lidThick+wallThickness);
}

module tray_cup_carve(wallThickness=trayWall, colored="#03FC30", cupHeight = 0){
    trans_z = wallThickness;
    translate([0,0,trans_z+(cutMinimalMargin)])
        tray_cup(wallThickness=wallThickness, colored=colored, cupHeight =cupHeight);
}

// Circle of tray is determined by trayWidth
// Keep the circle center at proper (minimum) distance,
// small tray; "extra distance" for circle from machine
// large tray; dependent on traywidth
function tray_circle_center_x() = ((trayWidth <= backblock[width]) || (trayWidth/2 < cupLength)) ? cupLength : trayWidth/2;

module tray_cup(wallThickness = 0, lid = false, colored="#BEFC03", holes = false, cupHeight=0, $fn=$preview?50:180){
    // Displace very minimal (preview only) to show a "clean" cutout (wallThickness > 0) in preview mode
    minimalMarginCut = wallThickness > 0 ? cutMinimalMargin : 0;

    // Add a tiny bit to "virtual" wall (smaller object), else fit will be too tight.
    wallThicknessSideWays = wallThickness > 0 ? wallThickness+0.2 : wallThickness;

    translate([0, trayWidth > backblock[width] ? 0 : ((backblock[width]-trayWidth)/2),0]) {
        // The tray cup consists of a cube and a cylinder
        
        translate([backblock[depth],wallThicknessSideWays,0]) color(colored)
            cube([maincup[depth], maincup[width]-(2*wallThicknessSideWays), cupHeight-(wallThickness)+minimalMarginCut ]); //main body of the tray

        // Circle tray positioning;
        // Traywidth <= backblock, fixed position,
        // else use diameter
        x =  tray_circle_center_x();
        translate([x, maincup[width]/2, 0 ])
            color(colored)
            cylinder(h=cupHeight-(wallThickness) ,d=trayWidth-(2*wallThicknessSideWays), $fn=$fn); // Rounded front of the tray

    }
}

// Tray back (cut), where tray hooks onto cups bin in machine
module tray_back(colored="yellow"){
    color(colored) {
        //Backblock set
        cube(backriseBlock); // Join tray onto back, fill the backrise
        // Backblock
        translate([0,0,backrise[height]])
            cube(backblock); // Backblock, part that hooks on the cups bin
        //Backblock set
    }
}

// Backfit (cut), safety cutouts for fitting into machine
module backfit( colored="red", alf = 0.3 ){
    color(colored, alpha=alf) {
        // "Negative" drawing for cutout
        // Actually resembles the actual coffee machine, a tiny bit ;-)
        difference()
        {
            // "Wall" where it needs to fit
            translate([-safeCut,-safeCut/2,-safeCut/2])
                cube([caseDepth+safeCut, backblock[width]+safeCut, backblock[height]+safeCut*2]);

            // regular backblock, just extended a bit higher
            cube([caseDepth+safeCut, backblock[width], backblock[height]+safeCut]);
        }
        translate([-cutMinimalMargin,0,-cutMinimalMargin])
            cube([ backrise[depth], backrise[width], backrise[height] ]); // Edge to ground, just within the case

        // Connection block at the back

        // Move to center of back
        backcenter = (backblock[width] /2);
        translate([-cutMinimalMargin, backcenter - (backconnectionBlock[width]/2), -cutMinimalMargin]) {
            cube(backconnectionBlock);

            translate([backconnectionBlock[depth]-backconnectionBlockEdge[depth],0,0])
                cube(backconnectionBlockEdge);
        }

        translate([-cutMinimalMargin, backcenter - (backconnectionBlockEdgeNudge[width]/2), 0])
            cube(backconnectionBlockEdgeNudge);
    }
}

module holes(height=5, r_hole=2, distance=7.4, rings=15, r_limit=100, $fn=$preview?10:50 ){

  // Number of holes in respective "ring" (7, 13, 19, 25, ....)
  function hole_nums(j) = 7+(j*6);

  cylinder(height,r=r_hole,center=true);
  for(j=[0:rings])
    for(i=[1:hole_nums(j)]) {
          if( (j+1)*distance > r_limit  ) {
          // translate([distance+(j*distance),0,0])
          //   cube(size = 5, center=true);
          } else {
            rotate([0,0,(i+j/3)*360/hole_nums(j)]) translate([(j+1)*distance,0,0]) cylinder(height, r=r_hole, center=true);
          }
    }
}

