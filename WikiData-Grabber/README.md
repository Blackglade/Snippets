WikiData-Grabber
================

### About ###

Upon running the script, it will return the following statistics


>* Page URL Address
>* Page Title
>* View Count (30, 60, 90 days)
>* Authors
>* Edits


### Usage ###

Declare a class object with the following parameters
```php
// Specifies URL to grab data from (Special:Random randomly generates a wikipedia page)
$url = "http://en.wikipedia.org/wiki/Special:Random";

// Specifies # of times to loop through and grab data of url
$num = 3;

// Specify last 30, 60, or 90 days to get page views from (Default: 90)
$days = 90;

$wiki = new WikiData($url, $num, $days)
```

Grab The Wikipedia Data
```php
// Specify true to create text file (Default: False)
$txt = true; 

// Specify Filename to output text to (Default: test.txt)
$file = 'wiki.txt';

$wiki->grabData($txt, $file);
```

### Sample Output ###

Output using a text file:
```
Here are your WikiData results!


Link: http://en.wikipedia.org/wiki/You%27re_My_Thrill_(song)
Title: You're My Thrill (song)
Views (90 Days): 838
Authors: 22
Edits: 30

Link: http://en.wikipedia.org/wiki/List_of_programs_broadcast_by_TVGN
Title: List of programs broadcast by TVGN
Views (90 Days): 2660
Authors: 17
Edits: 60

Link: http://en.wikipedia.org/wiki/Pre-Parliament_(Armenia)
Title: Pre-Parliament (Armenia)
Views (90 Days): 356
Authors: 6
Edits: 15
```

### Notes ###

* Could probably have made this faster by rewriting it in something like Javascript and running it with NodeJS but I'm lazy.

* A lot more data could be added to the script, but so far it only returns the Link, Title, Views, Authors, and Edits to keep things simple.

### License ###
	Released under the MIT License