# Arduino Italiano!

## History

The idea of creating Arduino took shape in 2003 at the IDII [^1] in Italy. The idea was to build a simple, low-cost device for students to carry out digital projects, especially those who did not have much familiarity with the principles of engineering and programming. Three key individuals played a role in realizing this idea: Hernando Barragán, Massimo Banzi, and Casey Reas.

Barragán was a student at the Ivrea Institute who decided to carry out his master's thesis in this field. Banzi and Reas were Barragán's thesis advisors. At that time, the name "Arduino" did not yet exist. The outcome of Barragán's thesis was highly successful and led to the creation of hardware and software called "Wiring." The Wiring hardware possessed the desired characteristics compared to other available products on the market at the time—namely, it was simple and low-cost. The Wiring software was also based on an existing programming language called "Processing."

After the completion of the thesis, Banzi set out to reduce the costs of the Wiring hardware. In 2005, in collaboration with David Cuartielles and David Mellis (who were, respectively, an employee and a student at the Ivrea Institute), he developed the Wiring project and changed its name to "Arduino." This new name was derived from a bar called "Arduino" in the town of Ivrea, where most of the group's meetings were held. The word "Arduino" is also the name of an ancient Italian king who was once the ruler of the town of Ivrea and became King of Italy in the 11th century. Gradually, the core team of Arduino was formed with five main individuals: Banzi, Cuartielles, Mellis, and two new members named Tom Igoe and Gianluca Martino. Among the members of this five-person group, Barragán's name (the thesis author) is not seen, and he was never invited to participate in this group. [^1]

![](Images/Interaction%20Design%20Institute%20Ivrea.png)


This five-person team registered the Arduino trademark in the United States in 2008. Around the same time, Martino, one of the members of this group, secretly registered the Arduino name for himself in Italy and began operating in parallel with the main company, personally producing and selling the product. The legal complexities that arose around the Arduino trademark forced the original company in the United States to use the trademark "Genuino" for selling its products outside of America. The specifications and features of Genuino boards are exactly similar to those of Arduino and have no difference from it.

The Arduino platform consists of both hardware and software components. This chapter introduces the Arduino hardware.

There are various models of Arduino boards available on the market, but the most suitable model for beginners is the **"Uno R3 DIP"** , and the explanations in this section of the book are presented according to this model. The word "Uno" means "one" in Italian. "R3" stands for Revision 3, indicating the third version of the Arduino Uno board, which has undergone revisions and improvements compared to its predecessors. The term "DIP" refers to the type of microcontroller used on the board, which will be explained below.

## Microcontroller: ATmega328P

The heart of the Arduino Uno R3 DIP is the **ATmega328P** microcontroller. This is the chip that executes the program you write. The "DIP" (Dual In-line Package) designation means that the microcontroller is housed in a package with pins that can be inserted into a socket on the board. This is a key feature for beginners because if the chip gets damaged, it can be easily removed and replaced without needing to solder or buy a new board.




