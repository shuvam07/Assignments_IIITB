from bs4 import BeautifulSoup
import requests 
import urllib3
import smtplib
from smtplib import SMTPException



urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)


username = raw_input("Enter lms username: ")
password = raw_input("Enter lms password: ")

mailFrom  = raw_input("Enter mail From: ")
mailFromPass = raw_input("Enter mail From password: ")

mailTo = raw_input("Enter mail To: ")

print "Retreiving Data"


links = []


payload = {'username': username, 'password': password}
url = 'https://lms.iiitb.ac.in/moodle/login/index.php'
res = requests.post(url, data=payload, verify=False)




soup = BeautifulSoup(res.text, 'html.parser')

for news in soup.find_all('div',class_='assign overview'):
	links.append(news.find('a')['href'])

#print links


Message  = "You have a new notification \n"
for link in links:
	Message = Message+(link+"\n")

sender = mailFrom
receivers = mailTo

#print Message

print "Sending Mail"

s = smtplib.SMTP('smtp.gmail.com', 587)
s.starttls()
s.login(mailFrom, mailFromPass)
message = Message
sent = s.sendmail(mailFrom, mailTo, Message)
s.close()

print "Mail sent successfully..."



#print res.text.prettify()