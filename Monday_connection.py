def create_item(adultsTemp,adultsHumid,laraveTemp,measurmentID):
    apiKey = 'eyJhbGciOiJIUzI1NiJ9.eyJ0aWQiOjIzNzkyNTIxMSwidWlkIjoxNTg2MzcxMiwiaWFkIjoiMjAyMy0wMi0xNlQyMjoyNzoxMi41NzFaIiwicGVyIjoibWU6d3JpdGUiLCJhY3RpZCI6Njk5MzQzNCwicmduIjoidXNlMSJ9.CeSxYrLQxn-8jN8O-TQaMk0YlSlmW-wlPuYEWjOAiG4'

    apiUrl = "https://api.monday.com/v2"
    headers = {"Authorization": apiKey}

    now = datetime.datetime.now().strftime("%m-%d %H:%M")

    query = 'mutation ($myItemName: String!, $columnVals: JSON!) { create_item (board_id:3984889513, item_name:$myItemName, column_values:$columnVals) { id } }'
    vars = {
        'myItemName': now,
        'columnVals': json.dumps({
            'numeric': adultsTemp,
            'numeric1': adultsHumid,
            'numeric6': laraveTemp,
            'text4': measurmentID
        })
    }

    data = {'query': query, 'variables': vars}
    r = requests.post(url=apiUrl, json=data, headers=headers)  # make request
    print(r.json())

def searchByColumnValue(column_value):
    # Replace *** with your actual API key
    apiKey = 'eyJhbGciOiJIUzI1NiJ9.eyJ0aWQiOjIzNzkyNTIxMSwidWlkIjoxNTg2MzcxMiwiaWFkIjoiMjAyMy0wMi0xNlQyMjoyNzoxMi41NzFaIiwicGVyIjoibWU6d3JpdGUiLCJhY3RpZCI6Njk5MzQzNCwicmduIjoidXNlMSJ9.CeSxYrLQxn-8jN8O-TQaMk0YlSlmW-wlPuYEWjOAiG4'

    apiUrl = "https://api.monday.com/v2"
    headers = {"Authorization": apiKey}


    # Define the query and variables
    query = 'query ($columnValue: String!){items_by_column_values(board_id:3984889513, column_id:"text4", column_value:$columnValue){id name}}'

    variables = {
        'columnValue': column_value
    }

    # Define the request parameters
    data = {'query': query, 'variables': variables}

    # Send the request
    response = requests.post(url=apiUrl, json=data, headers=headers)

    print(response.json())

    # Parse the response
    data = response.json()

    # Get the list of item IDs and names
    item_data = data['data']['items_by_column_values']
    item_ids = [item['id'] for item in item_data]
    item_names = [item['name'] for item in item_data]

    # Print the item IDs and names
    print('Item IDs:', item_ids)
    print('Item names:', item_names)

    if item_ids:
        item_id = str(item_ids[0])
        print(f"item_id: '{item_id}'")
    else:
        print("item_ids list is empty")

    if item_ids:
        return(item_id)

def moveItemToGroup(itemID,groupId):

    apiKey = 'eyJhbGciOiJIUzI1NiJ9.eyJ0aWQiOjIzNzkyNTIxMSwidWlkIjoxNTg2MzcxMiwiaWFkIjoiMjAyMy0wMi0xNlQyMjoyNzoxMi41NzFaIiwicGVyIjoibWU6d3JpdGUiLCJhY3RpZCI6Njk5MzQzNCwicmduIjoidXNlMSJ9.CeSxYrLQxn-8jN8O-TQaMk0YlSlmW-wlPuYEWjOAiG4'
    apiUrl = "https://api.monday.com/v2"
    headers = {"Authorization": apiKey}

    #query2 = 'query{boards(ids: 3984889513){groups{id title}}}' #to find group id

    query1 = 'mutation {move_item_to_group (item_id: %s, group_id: "%s") {id}}' % (itemID,groupId)

    variables = {
            'itemId': itemID,
            'groupId':groupId}


    data = {'query': query1}#,'variables':variables}
    r = requests.post(url=apiUrl, json=data, headers=headers)  # make request
    print(r.json())

def create_group():
    apiKey = 'eyJhbGciOiJIUzI1NiJ9.eyJ0aWQiOjIzNzkyNTIxMSwidWlkIjoxNTg2MzcxMiwiaWFkIjoiMjAyMy0wMi0xNlQyMjoyNzoxMi41NzFaIiwicGVyIjoibWU6d3JpdGUiLCJhY3RpZCI6Njk5MzQzNCwicmduIjoidXNlMSJ9.CeSxYrLQxn-8jN8O-TQaMk0YlSlmW-wlPuYEWjOAiG4'

    apiUrl = "https://api.monday.com/v2"
    headers = {"Authorization": apiKey}

    now = datetime.datetime.now().strftime("%d/%m/%y - %H:%M")
    group_name = now
    query = 'mutation {{ create_group (board_id: 3984889513, group_name: "{}", position:"1") {{ id }} }}'.format(group_name)

    data = {'query': query}
    r = requests.post(url=apiUrl, json=data, headers=headers)  # make request
    print(r.json())

def delete_item(itemId):
    apiKey = 'eyJhbGciOiJIUzI1NiJ9.eyJ0aWQiOjIzNzkyNTIxMSwidWlkIjoxNTg2MzcxMiwiaWFkIjoiMjAyMy0wMi0xNlQyMjoyNzoxMi41NzFaIiwicGVyIjoibWU6d3JpdGUiLCJhY3RpZCI6Njk5MzQzNCwicmduIjoidXNlMSJ9.CeSxYrLQxn-8jN8O-TQaMk0YlSlmW-wlPuYEWjOAiG4'

    apiUrl = "https://api.monday.com/v2"
    headers = {"Authorization": apiKey}


    query = 'mutation { delete_item (item_id: %s) { id } }' % itemId

    data = {'query': query}
    r = requests.post(url=apiUrl, json=data, headers=headers)  # make request
    print(r.json())