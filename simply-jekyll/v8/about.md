---
layout: post
title: About
permalink: /about/
content-type: eg
---

<div class="biography">
<table class="biobox disable-select">
<tbody>
<tr>
<th colspan="2" style="text-align: center; font-size: 110%; font-weight: bold">
<div style="display: inline;">Raghuveer S</div>
</th>
</tr>
<tr>
<td colspan="2" style="text-align: center">
<img id="profpic" src="/assets/img/pp2.jpg"/>
<div id="profpicDesc" class="very-small">Portrait from <i>LinkedIn</i>, 2020</div><br>
</td>
</tr>
<tr>
<th scope="row">Born</th>
<td> 7, மார்கழி, பவ
<div>Chennai, India</div></td>
</tr>
<tr>
<th scope="row">Lives</th>
<td>Bangalore, India</td>
</tr>
<tr>
<th scope="row">Alma mater</th>
<td><a href="https://vtu.ac.in/"><i>Vishweshwaraya Technical University</i></a></td>
</tr>
<tr>
<th scope="row">Main Interests</th>
<td>System Programming, Computer Graphics, Algebraic Geometry</td>
</tr>
<tr>
<th scope="row">Favorite Languages</th>
<td><i>C++, Rust, Lisp</i></td>
</tr>
<tr>
<th scope="row">CS Infl</th>
<td>John McCarthy</td>
</tr>
<tr>
<th scope="row">Ph Infl</th>
<td>Bertrand Russell</td>
</tr>
</tbody>
</table>
</div>

<span style="font-size:180%; font-style: italic;">R</span>aghuveer S(a.k.a Raghu; /rəˈgu:/; <span style="font-size: 10px">tamil:</span> ரகுவீர்) — a software engineer, with an expertise in Systems Programming; and a dilettante in the realm of Computer Graphics and Compiler Design.

I am also an avid reader, with a special inclination towards Philosophy. Some of my favorite philosophers/philosophical authors include Russell, Wittgenstein, Aristotle, Descarte, Kant, (embarrasingly so Heidegger), Borges, Montaigne, Taleb, Aurelius, and Seneca

My area of interests include Computer Science, Cognitive Science, Mathematics, and Philosophy; and I take special interest in learning things that weren't part of my school/college curiculum. For all I know, it might be because of my educational experience, given that most of my formative years were spent mistaking authority for correctness.

I also like to write a lot, mainly about things that interests me. Some of my writings are published in this blog and the other chunk(also the major chunk of my writing) remains unpublished. To see my personal repository of writing, you can reach out to me directly at [[raghu@raghuveer.net::mailto:raghu@raghuveer.net]].

Apart from reading and writing, I like to spend my spare time tinkering with small coding projects, which is hosted here: [[GitHub::https://github.com/raghuveerdotnet]]. You can reach out to me via [[twitter::https://twitter.com/raghuveerdotnet]] or via [[mail::mailto:raghu@raghuveer.net]], for what it's worth, I see and reply to each and every mail and dm I get.

Btw I now live in Bangalore, so If you happen to be in Bangalore by chance and want to chat, drop an email([[raghu@raghuveer.net::mailto:raghu@raghuveer.net]]) and include [Coffee] in the subject line, and we can work something out.
   

If you like anything about who I am or what I do, please do follow me or reach out to me. Don’t hesitate.


## About the website

- Domain is registered with Google Domains
- The site lives on [[Github::https://github.com/raghuveerdotnet/raghuveerdotnet.github.io]] and is served using Netlify
- This website is statically generated using Jekyll from a set of Markdown files.
- Font used is **Georgia** 
  - (My favorite (free) Serif font after Silk, Century Old, Bon Vivant, Adobe Garamond Pro, Begum, Adobe Carlson Pro, Almost every thing by Linotype, Silk Factory, and Sans and Sons)


Previous iterations of the website: [[Jan-22-2020::https://web.archive.org/web/20200122164405/raghuveer.net]], [[Apr-13-2020::https://web.archive.org/web/20200413193808/raghuveer.net]], [[Apr-20-2020::https://web.archive.org/web/20200420172058/raghuveer.net]]

<script>
const profilePics = {
   1: '/assets/img/pp1.jpg',
   2: '/assets/img/pp2.jpg'
}

Object.freeze(profilePics);

document.getElementById("profpic").addEventListener("click", function() {
   var iSrc = document.getElementById("profpic");
   var iSrcDesc = document.getElementById("profpicDesc");
   if (iSrc.src.match(profilePics[2])) {
      iSrc.src = profilePics[1];
      iSrcDesc.innerHTML = "Style Transfer(ML) of the Portrait";
   } else {
      iSrc.src = profilePics[2];
      iSrcDesc.innerHTML = "Portrait from <i>LinkedIn</i>, 2020";
   }
});

document.getElementById("profpic").addEventListener("contextmenu", function(e) {
   e.preventDefault();
   return false;
});


</script>