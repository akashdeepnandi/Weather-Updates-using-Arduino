<?php
    $dbServername = "localhost";
    $dbUsername = "root";
    $dbPassword = "";
    $dbName="w_db";

    $conn = mysqli_connect($dbServername, $dbUsername, $dbPassword, $dbName);

    $sql = "SELECT * FROM w_data ORDER BY w_id DESC LIMIT 1;";
    $result = mysqli_query($conn, $sql);

    if (mysqli_num_rows($result) > 0) {
        $row = mysqli_fetch_assoc($result);
        $str = "";
        foreach ($row as $val) {
            if ($str == "") {
                $str = $str.$val;
            } else
                $str = $str.",".$val;
        }

        echo $str;
    } else {
        echo "N";
    }
    
    