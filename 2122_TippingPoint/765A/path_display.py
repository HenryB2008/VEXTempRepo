import PIL 
from PIL import Image, ImageDraw
import matplotlib
import re 
import math
# function = input("Enter function name: ")

functiontext = ""

with open("src/main.cpp", "r+") as texthandle:
    file = ""
    for line in texthandle:
        file += line
    # searchstring = "void " + function + "(.*)\}void"
    searchstring = "void leftskills"
    match = file.index("newSkills")
    match2 = file.index("void leftskills")
    function = file[match + 15:match2-4]
    function = function.replace(" ", "")
    # function = function.replace("\n", "")
    # print(function)
    commands = function.split("\n")
    movements = []
    for command in commands:
        command = command.strip()
        if command.startswith("distanceMove") or command.startswith("dragTurn") or command.startswith("goal.theta"):
            movements.append(command)
    # for movement in movements:
        # print(movement)
    
    #635 width for 12 ft
    #52.9 px / ft and 4.4 px / inch
    #starting position = (85, 85)
    base_image = Image.open("skills_field.PNG")
    drawing = ImageDraw.Draw(base_image)
    drawing.ellipse([(70,70),(100,100)], "black", "black")
    currentheading = math.pi/2
    currentmovement = 1
    oldx = 85
    oldy = 105
    n = 1
    for movement in movements:
        if movement.startswith("distanceMove"):
            arguments = movement[movement.index("(")+1:movement.index(")")].replace(" ", "").split(",")
            # arguments = arguments.replace(" ", "")
            # arguments = arguments.split(",")
            # print(arguments)
            distance = int(arguments[0])
            direction = float(arguments[1])
            if direction > 0:
                currentmovement = -1
                # currentheading = (math.pi) + currentheading
                print("Backwards " + str(distance) + " pixels at " + str(currentheading*180 / math.pi) + "->" + str(math.pi + currentheading))
                newx = oldx + (distance * 4 * math.cos(math.pi + currentheading))
                newy = oldy - (distance * 4 * math.sin(math.pi + currentheading)) 
                print(newx, newy) 
            else:
                currentmovement = 1
                print("Forwards " + str(distance) + " pixels at " + str(currentheading*180 / math.pi) + "->" + str(currentheading))
                newx = oldx + (distance * 4 * math.cos(currentheading))
                newy = oldy - (distance * 4 * math.sin(currentheading))
                print(newx, newy)
            
            drawing.line([(oldx, oldy),(newx,newy)], "black", 2)
            oldx = newx
            oldy = newy
            # direction = int(arguments[1])

        if movement.startswith("goal.theta"):
            currentheading = (math.pi / 2) - (int(movement[movement.index("=")+1:movement.index("_")].replace(" ", "")) * math.pi / 180)
        if movement.startswith("dragTurn"):
            drawing.arc([(oldx, oldy),(oldx + 90, oldy + 90)], 180, 285, "black", 2)
            currentheading = (90-105)*math.pi / 180
            oldx = oldx + 45 + (45*math.cos(75/180*math.pi))
            oldy = oldy + (math.sin(75/180*math.pi))
        drawing.ellipse([(oldx-5,oldy-5),(oldx+5,oldy+5)], "black", "black")
        # drawing.ellipse
        n+= 1
        # if n > 9:
            # break
    base_image.show()