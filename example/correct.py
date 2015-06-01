# -*- coding: utf-8 -*-
import os, requests

# Try to correct the word using yandex apis
def correct(word, lang):
	params = {"text": word, "lang": lang}
	r = requests.get("http://speller.yandex.net/services/spellservice.json/checkText", params=params)

	if (r.status_code == 200):
		if (len(r.json()) > 0):
			out = r.json()[0]
			variants = [v for v in out['s']]
			if (len(variants) == 0):
				return word
			return variants[0].encode("utf-8")
		else:
			return word
	else:
		return word
