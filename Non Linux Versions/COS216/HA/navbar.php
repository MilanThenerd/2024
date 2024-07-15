<ul>
    <li><a href="auctions.php" class="<?php echo (strpos($_SERVER['REQUEST_URI'], '/auctions.php') !== false) ? 'button-sidebar-active' : 'button-sidebar'; ?><?php echo isset($_COOKIE['dark-mode']) && $_COOKIE['dark-mode'] === 'true' ? ' dark-mode' : ''; ?>">Auctions</a></li>
    <li><a href="userauctions.php" class="<?php echo (strpos($_SERVER['REQUEST_URI'], '/userauctions.php') !== false) ? 'button-sidebar-active' : 'button-sidebar'; ?><?php echo isset($_COOKIE['dark-mode']) && $_COOKIE['dark-mode'] === 'true' ? ' dark-mode' : ''; ?>">My Auctions</a></li>
    <li><a href="bids.php" class="<?php echo (strpos($_SERVER['REQUEST_URI'], '/bids.php') !== false) ? 'button-sidebar-active' : 'button-sidebar'; ?><?php echo isset($_COOKIE['dark-mode']) && $_COOKIE['dark-mode'] === 'true' ? ' dark-mode' : ''; ?>">Bids</a></li>
</ul>
