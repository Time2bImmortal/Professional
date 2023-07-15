# def send_email2(body, to_email):
#     # Set up your email settings
#     my_email = 'themosquitoesassociation@gmail.com'
#     my_password = 'uyqlsubglvmfjxgi'
#     smtp_server = 'smtp.gmail.com'
#     smtp_port = 587
#
#     # Create a multipart message
#     msg = MIMEMultipart()
#     msg['From'] = my_email
#     msg['To'] = to_email
#     msg['Subject'] = 'Temperature Alert'
#     msg.attach(MIMEText(body, 'plain'))
#
#     # Send the email
#     server = smtplib.SMTP(smtp_server, smtp_port)
#     server.starttls()
#     server.login(my_email, my_password)
#     text = msg.as_string()
#     server.sendmail(my_email, to_email, text)
#     server.quit()