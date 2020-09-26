---
layout: post
title: By Tags
permalink: /tags/
content-type: eg
---

<style>
.category-content a {
    text-decoration: none;
    color: #4183c4;
}

.category-content a:hover {
    text-decoration: underline;
    color: #4183c4;
}
</style>

<main>
    {% for tag in site.tags %}
        <h3 id="{{ tag | first }}" style="font-family: Georgia, Garamond, book antiqua, bookman old style, Palatino, palatino linotype, times cy, times new roman, serif">{{ tag | first }}</h3>
        {% for post in tag.last %} 
            <li id="category-content" style="padding-bottom: 0.6em; list-style: none; font-size: 16px !important; font-family: Georgia, Garamond, book antiqua, bookman old style, Palatino, palatino linotype, times cy, times new roman, serif"><a href="{{post.url}}">{{ post.title }}</a></li>
        {% endfor %}
    {% endfor %}
    <br/>
    <br/>
</main>