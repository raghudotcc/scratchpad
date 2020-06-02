# note-complete README

This is only useful if you are using my jekyll theme with notes-autocomplete feature. All you have to do is copy this folder to .vscode/extensions directory and restart vscode if it is running.

## What does it do?

This plugin allows you to autocomplete files as you type wiki-style links.

For ex: if you had 6 files with title abc, adr, xyz, lmn, opq, rst; and you started typing `[[`, this plugin will provide a autocomplete dropdown as you type `[[`. Not just that, this plugin also is context aware i.e., if you type `[[a` and then type d like this - `[[ad`, it will only show you `adr` in the dropdown.

## Requirement:

Have a file called `autocomplete.txt` in your jekyll root directory with the following content.

```liquid
---
---
{%- for post in site.posts -%}
{{ post.title | strip_html | escape }};
{%- endfor -%}
{%- for post in site.notes -%}
{{ post.title | strip_html | escape }}{% unless foorloop.last %};{% endunless %}
{%- endfor -%}
```

## And viola! It should start working magically.
