Home Composting Bioreactor
==========================

This is the documentation and source code for a Home Composting Bioreactor.

Project overview
----------------
The goal of this project is to create a domestic appliance that takes all
the organic residues of a home and convert to a living organic fluid that is
suitable for growing vegetables and medicinal cannabis.

Currently I use a Joraform JK270 to compost all my residues and some neighbour's,
then I feed the comopost to worms, then I put the resulting compost into the
bioreactor.

This is based on the latest discoveries about the Rizophagic Cycle and several
projects in Youtube.

The bioreactor has several parts:

- Lower Container

  - Water pump
  - Biological media
  - Air difusor
  - Water level sensor

- Nutrient Router

  - 8 output channels (12v DC solenoid valves)
  - 1 circulation channel (220v AC 1'' solenoid)

- Electrical Panel

  - 1 Arduino Uno
  - 10 mosfets w/ 12v DC output
  - 3 SSR relays w/ 220v AC output
  - 20A 12v power source

- Water Input

  - 1 12v DC solenoid valve
  - Triple filter to remove chlorine (beer making gear)

- Air Pump

- Nutrient Chamber

  - Decantation media
  - particle filter

- Upper Container

  - Container with particle filter

Lower Container
---------------

This is where the main activity happens. This container has connections to receive
water input, that also receives nutrient solution that circulates back. On the
bottom of the container there is a rain water pump with 1'' output. Around the pump
there is a hose with micro holes to aerate the bottom, in a circular shape.
Holding the hose in the bottom, 5 bags of ceramic biological media, receiving air
direct from the air pump.

When the pump is turned on, water is pumped from the bottom to the router. The pump
needs a minimum level of fluid to be turned on, otherwise it does not work. It's
originally designed to pump rain water from a collector to a higher output.
The water level sensor indicates a level that is above that thresold.

Installed here there's also PH, temperature and TDS sensor, but the connecting wires
are too short to reach the Arduino Uno, so I plan to connect them to an Arduino Nano
and use a data cable to connect them. Currently the air pump is not connected
to the Electrical Panel, it's always on. I plan to also have CO2 and NH4 level sensor
and to stop the air pump for short periods of time to analyze the aerobial an anaerobial
activity.

Nutrient Router
---------------

This is a 1'' pipe with 9 outputs. The main one, 1'' output, is controled by a 220v AC
solenoid valve connected to a SSR. The other 8 outputs have reductions to 1/2'' or 3/4''
connected to 12v DC solenoid valves.

One of this minor outputs routes the nutrient solution to the nutrient chamber, that
has a particle filter and worm castings with worms. All the fluid from that chamber
are routed back to the Lower Container.

The main output routes the nutrient solution to the upper chamber. From there it's
distributed by gravity to bioponical trays spread in the house and gets back to
the Lower Container.

The other 7 minor channels are irrigation channels that go to vegetables in several
sites, and are not routed back. Since the channels can be narrow, it's important that
prior to routing the nutrient solution, the first pumped fluid, from the bottom of the
Lower Chamber, is pumped to the Upper Chamber to be filtered and decantated there,
so to avoid clogging.

Electrical Panel
----------------

This has a power source, an Arduino Uno and SSRs and mosfets to control all the pumps
and valves. It also reads the water level sensor. It's an iron box that protects
all components from the weather.

Water Input
-----------

There is a triple filter, a common setup sold in brew shops, that holds small particles
and removes chlorine from the water, which is important for the bacteria. Right after
the filter, a 12V DC solenoid valve, connected to the Lower Container input channel.

Air Pump
--------

The Air Pump is connected to an air input in the Lower Container and is also controlled
by the Arduino. While the CO2 and NH4 sensors are not implemented, it's directly on
220v current. It heats a lot.

Nutrient Chamber
----------------

This is a plastic container, with pebles in the bottom and geotextile fabric clued to
the container with aquarium grade sylicon. The worm castings, with worms, go in this
chamber. It receives the nutrient solution, that passes here and gets back to the
Lower Container with higher concentration of nutrients and bacteria.

Upper Container
---------------

This is a container on the top of the roof that receives the nutrient solution from the
Lower Container and distribute it back to there. On the future it will have biological
media and an air pump. Other than distribution, it filters and decantates the nutrient
solution that comes from the bottom of the Lower Container, to avoid clogging of the
irrigation channels.
