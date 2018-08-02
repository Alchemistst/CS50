# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

It's certainly a very long word.

## According to its man page, what does `getrusage` do?

It returns a struct with resources parameters, such as CPU time, shared memory, etc. among others.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 members

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

I'm not quite sure, to be honest, but I think it has something to do with the fact that there's the possibility for this values to be NULL,
in which case the behaviour of the program might erroneous. A "segmentation fault" probably.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

You guys are so annoying... Why you make us write so much!... Anyway...

First of, how many times the for loop will be going? fgetc takes the current char at the stream, then it makes sure is not EOF (end of the document), and then reads another character.
Effectively, the for loop will be running until there're no more chars to run through.

Now that we have the char read from the file there are 3 possible outcomes.

The first one is if the char is an alphabetic character or apostrophe, being the index greater than 0 (otherwise means the apostrophe is not part of a word). Then it proceed to store the char into the array (or string) word.
Afterwards, it checks in case the word is getting longer than we are expecting, in which case it discards the word (that's what the while loop does, it goes through all the char until a space is hit). Index is then
set to 0 and rinse and repeat.

The second outcome is for the character to be a digit, in which case we consume the rest of the word equally as we in the previous case, also setting the index to 0.

And the third outcome is really that, being the index greater than 0 (this means, we are currently reading a word), we hit something that is not a alphachar nor a digit... then must be a sapace! Meaning that the word is
finished. /0 for the string to complete it. Shove it on the misspelling function, update counters if misspelled, and bla bla bla.

And that's all folks! Guys, I really read the file, why you made write all this? Arg!

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Pneumonoultramicroscopicsilicovolcanoconiosis is the answer. We might get words longer than that. Maybe because someone missed a space or something, and horrible segmentation faults will appear and do bad things to you.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Well, is a very wise thing to do indeed! Those things are being passed pointers. If they weren't const's we could
accidentally (or not so accidentally if you are a mean hacker) change them and get segmentation faults, or
touch memory in places where we should not touch. I'd like to rise awareness to all those memories that have
been touched in places where they shouldn't have been touched. Segmentation fault is not a joke.
