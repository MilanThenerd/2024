<?php ?>
<!DOCTYPE html>
<html>
<head>
    <title>Files List</title>
    <style type="text/css">
        .folder {
            background-color: #fffddd;
            font-weight: bold;
            font-size: larger;
            padding: 2px;
        }

        li {
            padding: 4px;
        }
        .content {
            display: block;
            position: relative;
            padding: 10px;
            width: 90%;
            margin: 0 auto;
        }
    </style>
</head>
<body>
<div class="content">
    <h1>COS216</h1>
    <h2>File&Folder Structure</h2>

        <?php
            function listFolderFiles($dir){
                $ffs = scandir($dir);

                unset($ffs[array_search('.', $ffs, true)]);
                unset($ffs[array_search('..', $ffs, true)]);

                // prevent empty ordered elements
                if (count($ffs) < 1)
                    return;

                echo '<ol>';
                foreach($ffs as $ff){
                    if(is_dir($dir.'/'.$ff))
                        echo '<li><span class="folder">'.$ff."</span>";
                    else echo '<li><a href="'.$dir.'/'.$ff.'" target="_blank">'.$ff."</a>";

                    if(is_dir($dir.'/'.$ff)) {
                        listFolderFiles($dir.'/'.$ff);
                    }
                    echo '</li>';
                }
                echo '</ol>';
            }
            listFolderFiles('.');
        ?>
</div>

</body>
</html>
