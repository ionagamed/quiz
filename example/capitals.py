# -*- coding: utf-8 -*-
import correct, random

conf =	{
	"colorStep": 0.08,
	"font": "/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf",
	"title": "Уникальный шанс узнать больше столиц!\nПроверим перевод строки"
}

def checker(ans, inp):
	res = False
	msg = ""
	corr = correct.correct(inp, "ru")
	if (ans == corr):
		res = True
		if (corr != inp):
			msg = "(точнее: " + corr + ")"
	return {
		"result": res,
		"msg": msg
	}

def main():
	tmpDict = {
		"России": "Москва",
		"Индонезии": "Джакарта",
		"Малайзии": "Куала-Лумпур",
		"Филиппин": "Манила",
		"Австралии": "Канберра",
		"Тайланда": "Бангкок",
		"Израиля": "Иерусалим",
		"Кипра": "Никосия",
		"Японии": "Токио",
		"Китая": "Пекин",
		"Монголии": "Улан-Батор",
		"Армении": "Ереван",
		"Эквестрии": "Кантерлот"
	}
	resList = []
	for country in tmpDict:
		resList.append({
			"question": "Столица " + country,
			"answer": tmpDict[country],
			# input goes on b
			"checker": checker
			# "checker": lambda a, b: a == b
		})
	return random.sample(resList, 5)
