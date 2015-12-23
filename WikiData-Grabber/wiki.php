<?php
/*
 *
 * WikiData PHP Grabber
 * By Harsh Baid (Blackglade)
 * =============================================================================
 * Grabs Wikipedia Statistics and outputs them to a text file.
 * =============================================================================
 * Released under the MIT License by Harsh Baid (Blackglade)
 *
*/


// Lets Turn On Error Reporting!
ini_set('display_errors', 1);
error_reporting(E_ALL);


class WikiData{

	// Some Basic Global Variables
	public $repeat;
	public $days;
	public $url;

	// Sets Basic Parameters For URL + Repition + Days (30, 60, 90)
	public function __construct($url, $repeat, $days=90){
		$this->url = $url;
		$this->repeat = $repeat;
		$this->days = $days;

	}

	// Grabs The Article Data and Parses it to individual functions
	public function grabData($txt=false, $file='test.txt'){
		
		$result = "<h1>Here are your WikiData results!</h1>";
		
		// The Main ForLoop
		for($i = 0; $i < $this->repeat; $i++){
			$url = file_get_contents($this->url);
			$link = $this->getLink($url);
			$title = $this->getTitle($url);
			$views = $this->getViews($title);
			$authors = $this->getAuthors($title);
			$edits = $this->getEdits($title);

			$content = "<br /><br /><b> Link:</b> ".$link."<br /><b> Title:</b> ".$title."<br /><b> Views (90 Days):</b> ".$views."<br /><b> Authors:</b> ".$authors."<br /><b> Edits:</b> ".$edits."";
			$result .= $content;
		}
		
		// For File Creation
		if($txt){
			$result = str_replace("<br />", "\n", $result);
			$result =  strip_tags($result, "<br />");
			file_put_contents($file, $result);
		} else{ echo $result; }
	}

	// Returns The Title + Page Link of Page
	public function getLink($url){
		if(strlen($url) > 0){
			preg_match("/\<link rel=\"canonical\" href=\"(.*)\" \/>/",$url,$info);
			return $info[1];
		}
	}

	// Returns Main Title Of Page
	public function getTitle($url){
		if(strlen($url) > 0){
			preg_match("/\<title\>(.*)\<\/title\>/",$url,$info);
			$info = str_replace(" - Wikipedia, the free encyclopedia", "", $info[1]);
			return $info;
		}
	}

	// Gets The Views of Wikipedia Page
	public function getViews($title){
		if($this->days%30 == 0){
			$title = str_replace(" ", "_", $title); // Because PHP parses the url incomplete
			$json = "http://stats.grok.se/json/en/latest" . $this->days . "/" . $title;
			$json = json_decode(file_get_contents($json), true);
			$total = 0;
			foreach($json as $a => $b)
				if(is_array($b))
					foreach ($b as $key)
						$total += $key;
			return $total;
		}
	}

	// Gets The Author of Wikipedia Page
	public function getAuthors($title){
		$title = str_replace(" ", "_", $title); // Because PHP parses the url incomplete
		$url = file_get_contents("http://en.wikipedia.org/w/index.php?title=".$title."&action=info");
		if(strlen($url)>0){
			preg_match("/Total number of distinct authors<\/td><td>(.*?)<\/td>/", $url, $info);
			return $info[1];
		}
	}

	// Gets The Edits of Wikipedia Page
	public function getEdits($title){
		$title = str_replace(" ", "_", $title); // Because PHP parses the url incomplete
		$url = file_get_contents("http://en.wikipedia.org/w/index.php?title=".$title."&action=info");
		if(strlen($url)>0){
			preg_match("/Total number of edits<\/td><td>(.*?)<\/td>/", $url, $info);
			return $info[1];
		}
	}
}

?>