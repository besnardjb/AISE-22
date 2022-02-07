<html>

<body>

<?php

$redis = new Redis();
$redis->connect('myredis', 6379);

$range = $redis->hkeys("words");

$words = array();

foreach($range as $e)
{
    $count = $redis->hget("words", $e);
    array_push($words, array("word" => $e, "count" => $count));
}

function cmp($a, $b)
{
    return $b["count"] - $a["count"];
}

usort($words, "cmp")

?>

<h1>REDIS</h1>


<table>
<?php
foreach($words as $e)
{
    echo "<tr><td>".$e['word']."</td><td>".$e["count"]."</td></tr>";
}
?>
</table>


</body>


</html>
