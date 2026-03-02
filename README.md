# CS300-DSA-Analysis-and-Design-Project
Project One and Two for this class including a reflection on the project. 

<b>What was the problem you were solving in the projects for this course?</b><br>
  The problem I was solving was to build an advising assitant for ABCU Computer Science department. The advisors
  needed to be able to load data from a CSV file, print a sorted list of all CS courses in alphanumeric order,
  and be able to look up any individual course to display its title and prerequisites all in one program. I needed
  to ensure that this program was designed thoughtfully in order to be efficient and be able to handle any 
  real-world situations. For example if there were missing prerequisites, inconsistent input from the user, and 
  malformed input lines.
<br><br>

<b>How did you approach the problem? Consider why data structures are important to understand.</b><br>
  Starting in Project One, I first designed pseudocode. The pseudocode was for three different data structures
  that were being considered for the program: vector, hash table, and binary search tree. I then peformed Big O 
  analysis on each to see which would be the best data structure for handling the data. 
<br>
  Vector sort used used used bubble sort in order to sort the course list which operates at O(n^2). Hash table was 
  O(1) average lookup but then all the courses needed to be pulled into a temporary vector to sort all the courses 
  each time the list was printed. Then the BST inserted courses at O(log n) average and produced the ordered list 
  using in-order traversal at O(n) and there was no separate step needed to sort the courses in alphanumeric order. 
  This analysis is what helped me choose the best data structure to use in which I chose the BST for the program's
  implementation in Project Two.
<br>
  The process of looking at the different data structures and using Big O analysis helped give me an understanding
  of why data structures matter in a program beyond just theory. All three data structures are able to store and
  return all the same data, but the data structures have their pros and cons which were easier to see by looking
  at pseudocode for the structures. It's important to choose the data structure that will efficiently handle what 
  the program needs to do most often.
<br><br>

<b>How did you overcome any roadblocks you encountered while going through the activities or project?</b><br>
  One challenge or roadblock I faced actually came directly from feedback I received from my Project Once psuedocode.
  The menu loop was correct with enforcing the "load first" rule and was able to handle invalid numeric selections,
  however, it would benefit more from a stronger input-type validation such as handling any non-numeric input and a 
  clearer normalization of course IDs. This was useful feedback that served as a reminder to think about user
  input to be able to not only catch obvious errors but to be able to provide a response regardless of how a user
  inputs rather than unexpected behavior.
<br>
  I ended up addressing this in Project Two. Instead of using /cin>>choice/, I switched to reading the full input 
  line as a string with /getline/. Then I used /isdigit()/ to chck every character before using /stoi()/ to convert. 
  I then built /NormalizeCourseID()/ function for course ID normalization to trim whitespace and conver to uppercase.
  Therefore the program would be able to locate the correct course regardless of if the input is lowercase or
  uppercase. 
<br><br>

<b>How has your work on this project expanded your approach to designing software and developing programs?</b><br>
  Before this course, I didn't like to write pseudocode. I wanted to dive into coding and figure out as I go. Working
  through this course of building out my pseudocode first with the data structures, writing out the program and analyzing
  helped show how important it is to use pseudocode before diving into the code. By the time it was time for me to work
  on Project Two, my data structure was chosen and the architecture was laid out for me. Although I need to make some
  changes based on feedback from Project One, I was able to easily implement the code for the program. The design portion
  and writing the pseudocode isn't a waste of time and is actually important to the process. It helps with efficient
  coding as I didn't have to make any changes with the code itself, just with the design and then easily lay it out 
  in code.
<br><br>

<b>How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?</b><br>
  This project has taught me to be intentional about all of these qualities. In regards to reability, I made an effort 
  in this project to use clear naming conventions and to include important in-line comments. I want to continue to do
  this in future projects and expand more on in-line comments to provide more context for what the line of code does
  in a broader way in the program rather than just narrating. For maintainability, separating to distinct functions makes
  it easy to update or debug one piece without having to touch the other functions. And for adaptability, being able to 
  build around a data structure whose performance I could predict, meant that the program is able to absorb different 
  changes such as using a larger course catalog or additional menu options without having to redesign the program from
  scratch. The projects in this course helped show that writing code is only a part of the job and that designing code 
  that others can maintain, read, and build upon is what helps make your program actual professional software. 
