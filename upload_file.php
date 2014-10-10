<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title>Titre</title>
    </head>
    <body>
<?php
require("rb.php");
$allowedExts = array("gif", "jpeg", "jpg", "png", "bmp");
$temp = explode(".", $_FILES["file"]["name"]);
$extension = end($temp);
if ((($_FILES["file"]["type"] == "image/gif")
|| ($_FILES["file"]["type"] == "image/jpeg")
|| ($_FILES["file"]["type"] == "image/jpg")
   || ($_FILES["file"]["type"] == "image/pjpeg")
|| ($_FILES["file"]["type"] == "image/x-png")
   || ($_FILES["file"]["type"] == "image/bmp")
   || ($_FILES["file"]["type"] == "image/png"))
   && in_array($extension, $allowedExts)) {
   if ($_FILES["file"]["error"] > 0) {
echo "Return Code: " . $_FILES["file"]["error"] . "<br>";
} else {
echo "Type: " . $_FILES["file"]["type"] . "<br>";
echo "Size: " . ($_FILES["file"]["size"] / 1024) . " kB<br>";
move_uploaded_file($_FILES["file"]["tmp_name"],
"upload/" . $_FILES["file"]["name"]);
echo "Stored in: " . "upload/" . $_FILES["file"]["name"];
echo "<br/>";
$filename = "upload/" . $_FILES["file"]["name"];

//R::setup('mysql:host=195.154.71.62;dbname=ocr','ocr','ocr');
//$newfile = R::load('pictures');
//$newfile['filename'] = $filename;
//$id = R::store($newfile);

echo "<img src=" . $filename . " border=\"1\" align=\"center\" width=70% height=70%/>";
  }
} else {
  echo "Invalid file";
}
?>
    </body>
</html>

