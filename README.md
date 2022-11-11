# QT-Calculator
A Small Graphical Calculator, made in QT and C++.

The Design of the grid layout was achieved using QT Designer which is very useful, even though normally I'd rather implement the design in code. Then the digit precision of the output display label is set as well as setting the number of trailing digits.

The math operations (Add, Sub, Mult, Divide) are all handled by the same callback function MathNumPressed which discriminates the operation based on which particular button was pressed. The lambda functions in the connect statements are used efficiently to show how this is all managed.

https://user-images.githubusercontent.com/111576658/201343013-8e3caa25-2ef3-4e44-b423-07a5a1fad3a9.mp4

