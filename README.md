# Rail Fence Cipher
A rail fence cipher I wrote in C in the middle of the night in about an hour

## Usage
```
Enter plaintext: supersecret
Enter key: 4
Encrypted with key 4: seuscprrtee
```

## How it works
### Encoding
---
In most rail fence cipher algorithms, a matrix is created with the dimensions of the key times the length of the plaintext. The plain text is then "zig-zagged" between the rails starting with the first one. An example is below.

`Plaintext: verysecrettext`  
`Key: 3`  
```
v . . . s . . . e . . . x .
. e . y . e . r . t . e . t
. . r . . . c . . . t . . .
```
Then the rails are squashed down, eliminating free space between letters, and concatenated to produce the ciphertext.  
(notice how half of the rail matrix goes unused after the text is squashed)
```
v s e x . . . . . . . . . .
e y e r t e t . . . . . . .
r c t . . . . . . . . . . .
```
```
"vsex" + "eyertet" + "rct" = "vsexeyertetrct"
```
`Ciphertext: vsexeyertetrct`

### Decoding
---
The way most rail fence cipher decoding algorithms work is by creating a matrix with the dimensions of the key times the length of the plaintext, and then generating the same zig-zag pattern but with some kind of marker character. In this case, a zero.

`Ciphertext: vsexeyertetrct`  
`Key: 3`
```
0 . . . 0 . . . 0 . . . 0 .
. 0 . 0 . 0 . 0 . 0 . 0 . 0
. . 0 . . . 0 . . . 0 . . .
```
Then, the ciphertext is placed rail by rail back into the matrix at the positions specified by the marker characters
```
[vsex]eyertetrct
v . . . s . . . e . . . x . <==
. 0 . 0 . 0 . 0 . 0 . 0 . 0
. . 0 . . . 0 . . . 0 . . .

vsex[eyertet]rct
v . . . s . . . e . . . x .
. e . y . e . r . t . e . t <==
. . 0 . . . 0 . . . 0 . . .

vsexeyertet[rct]
v . . . s . . . e . . . x .
. e . y . e . r . t . e . t
. . r . . . c . . . t . . . <==
```
The plaintext is now visible. By iterating through the matrix in a zig-zag pattern, you can produce the plaintext again.  
`Plaintext: verysecrettext`

## Optimization
### Encoding
---
I realized that it isn't actually neccessary to lay the plaintext out in a zigzag pattern before squashing it. By iterating through the plaintext and keeping track of the last empty space in each rail it is possible to create squashed rails in a single step. So this program allocates a matrix with *half* the length of the plaintext for the reason mentioned above.
```
v s e x . . . # # # # # # #
e y e r t e t # # # # # # #
r c t . . . . # # # # # # #
```
Why half? Because under the smallest possible key (2), the plaintext will be divided equally between two rails, causing each rail to contain half the total letters of the plaintext. As the key increases, the required length of the rails becomes shorter and shorter as the plaintext is divided up between more of them.


`Key: 2`
```
v . r . s . c . e . t . x .
. e . y . e . r . t . e . t
```
```
               Empty Space
              ______|______
             |             |
v r s c e t x . . . . . . .
e y e r t e t . . . . . . .
```
### Decoding
---
The nice thing about decoding is that you can create a [jagged array](https://en.wikipedia.org/wiki/Jagged_array) by iterating through the zig zag function for each letter in the ciphertext and counting how many times each rail is passed through, instead of generating a true zig zag shape. This allows us to allocate the exact amount needed for each rail.  
(Notice how the array below has the same number of 0s on each line as [the one above](#decoding))

`Ciphertext: vsexeyertetrct`  
`Key: 3`
```
0 0 0 0
0 0 0 0 0 0 0
0 0 0
```
The subsequent amount of letters from the ciphertext can then be inserted into each rail before zig zagging through the rails again to generate the plaintext
```
[vsex]eyertetrct
v s e x       <==
0 0 0 0 0 0 0
0 0 0

vsex[eyertet]rct
v s e x
e y e r t e t <==
0 0 0

vsexeyertet[rct]
v s e x
e y e r t e t
r c t         <==
```
Now I know it might not look like plaintext, but we are one step away from obtaining it.

Now that all the rails are filled, the last step is to perform a zig-zag between them one letter at a time to get the plaintext. By counting the number of times you pass each rail, you can generate a sort of index counter so you know which space to access next in the rail. So, the first time you pass the first rail you get the letter at index 0, the next time you get the letter at index 1 and so on.

It is a little hard to visualize, but try drawing a line over the array below over each letter in alphabetical order. Notice how it still forms a zig zag without missing any spaces.

`Plaintext: abcdefghijklmnop`  
`Key: 3`
```
A E I M
B D F H J L N P
C G K O
```