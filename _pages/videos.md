---
layout: inner
title: Videos
permalink: /videos/
---
{% for video in site.data.videos %}

<iframe src="https://www.youtube.com/embed/{{ video.id }}" frameborder="0" allowfullscreen></iframe>

{% endfor %}