<div class="sidebar">
    <h2>Pages</h2>
    <ul>
        <li><a href="listings.html" <?php if ($currentPage == 'listings') echo 'class="button-sidebar-active"'; ?>>Listings</a></li>
        <li><a href="agents.html" <?php if ($currentPage == 'agents') echo 'class="button-sidebar-active"'; ?>>Agents</a></li>
        <li><a href="calculator.html" <?php if ($currentPage == 'calculator') echo 'class="button-sidebar-active"'; ?>>Calculator</a></li>
        <li><a href="favourites.html?sort=fav" <?php if ($currentPage == 'favourites') echo 'class="button-sidebar-active"'; ?>>Favourites</a></li>
    </ul>
</div>